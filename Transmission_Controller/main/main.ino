// https://wokwi.com/projects/new/arduino-uno
// https://ww2-secure.justanswer.com/uploads/bobover/2011-02-05_023022_line_pressure_test_4r70w.pdf

const String VERSION = "11.27.23.1";
// const bool ENABLE_CAN_BUS;

#include <SPI.h>
#include <mcp2515.h>

// https://github.com/autowp/arduino-mcp2515

#pragma region notes
// TODO
// tcc lockup on high heat
// tcc unlock = 20%
// tcc lockup time 3 seconds 30%-70%
// tcc unlock on throttle off?
// unlock tcc before you shift 0.1 seconds
// rolling start?
// time overflow
// reverse?

// mcp2515 pinout
// cs =  48 digital pin grey
// si = 51 bottom blue
// so = 50 purple
// sck = 52 green
// int = n/a

// EPC
// Line Pressure = 0.389x +56.1
// 290hz?
#pragma endregion notes

#pragma region variables

struct can_frame canMsg;
struct can_frame canMsg1;
MCP2515 mcp2515(48);
struct BroadcastPacket
{
  long recvdtime = 0;
  int tpsvalue;
  // int dataid = 1523;  //this is the id of the realtime data broadcasting packet
  int dataid = -13;
  int other1;
  int other2;
  int other3;
};

BroadcastPacket bp = {};

enum CurveName
{
  FirstUP = 0,
  SecondDown = 1,
  SecondUp = 2,
  ThirdDown = 3,
  ThirdUp = 4,
  FourthDown = 5
};

struct Curve
{
  CurveName curvename;
  float y0;
  float y100;
  float slope;
  int PressureWhileShiftingSetpoint;
  int PressureInGearSetpoint;
};

// Shift Curves--------------------------
// 1st gear UP = 0.389x +5.11
//
// 2nd gear DOWN = 0.333x +3.67
// 2nd gear UP = 0.778x +10.2
//
// 3rd gear DOWN = 0.722x +8.78
// 3rd gear UP = 1.17x +14.3
//
// 4th gear DOWN = 1.06x +13.4

Curve olddefaultcurves[6] = {
    {FirstUP, 5.11, 44.01},
    {SecondDown, 3.67, 36.67},
    {SecondUp, 10.2, 88},
    {ThirdDown, 8.78, 80.98},
    {ThirdUp, 14.3, 131.3},
    {FourthDown, 13.4, 119.4}};

Curve defaultcurves[6] = {
    {FirstUP, 5, 35, 0, 20, 50},
    {SecondDown, 4, 30, 0, 20, 50},
    {SecondUp, 30, 70, 0, 20, 50},
    {ThirdDown, 20, 50, 0, 20, 50},
    {ThirdUp, 50, 100, 0, 20, 50},
    {FourthDown, 35, 80, 0, 20, 50}};

struct Curve2
{
  CurveName curvename;
  int shiftpoints[11];
  int PressureWhileShiftingSetpoint;
  int PressureInGearSetpoint;
};

Curve2 bettercurves[6] = {
{FirstUP,     {7, 7, 10, 12, 15, 18, 22, 27, 33, 40, 40}, 0, 1},
{SecondDown,     {3, 3, 5, 5, 5, 5, 10, 17, 23, 30, 30}, 0, 1},
{SecondUp,     {30, 30, 30, 30, 32, 38, 43, 50, 59, 70, 70}, 0, 1},
{ThirdDown,     {20, 21, 22, 22, 24, 27, 30, 36, 42, 50, 50}, 0, 1},
{ThirdUp,     {46, 46, 50, 50, 55, 65, 75, 85, 93, 100, 100}, 0, 1},
{FourthDown,     {35, 35, 36, 38, 40, 50, 55, 63, 71, 80, 80}, 0, 1}
};

class Timer
{
private:
  unsigned long currentTime;
  int timerLength;
  void (*callback)();

public:
  Timer(void (*callback)() = NULL, int length = 0)
  {
    this->callback = callback;
    this->timerLength = length;
  }

  unsigned long timerLastStart;
  unsigned long timerLastStop;
  bool isRunning;
  Curve ShiftCurve;

  void start(int length, Curve curve)
  {
    currentTime = millis();
    timerLastStart = currentTime;
    timerLastStop = 0;
    timerLength = length;
    ShiftCurve = curve;
    isRunning = true;
  }

  void stop()
  {
    currentTime = millis();
    timerLastStop = currentTime;
  }

  /// @return start - current
  unsigned long ElapsedTime()
  {
    return currentTime - timerLastStart;
  }

  bool timerExpired()
  {
    currentTime = millis();
    if (currentTime > (timerLastStart + timerLength))
      return true;
    else
      return false;
  }

  void Run()
  {
    if (!this->isRunning)
    {
      return;
    }

    // increment the timers
    currentTime = millis();
    if (this->timerExpired())
    {
      this->isRunning = false;
      if (this->callback != NULL)
      {
        this->callback();
      }
    }
  }
};

class PID
{
private:
  double Kp;
  double Ki;
  double Kd;

  double pre_error;
  double integral;
  double lastOutput;

public:
  // Constructor
  PID(double P, double I, double D)
      : Kp(P), Ki(I), Kd(D), pre_error(0), integral(0) {}

  int calculate(double setpoint, double pv)
  {
    // Calculate error
    double error = setpoint - pv;

    // Proportional term
    double Pout = Kp * error;

    // clamping the Integral term

    integral += error;

    integral = constrain(integral, -1000, 1000);

    double Iout = Ki * integral;

    // Derivative term
    double derivative = (error - pre_error);
    double Dout = Kd * derivative;

    // Calculate total output
    int output = (int)Pout + Iout + Dout;

    // Save error to next loop
    pre_error = error;

    // clamp the output

    lastOutput = output;
    output = constrain(output, 0, 255);

    return output;
  }
};
PID pid(.1, .1, .1);

int EPCSetpoint = 50;

// INPUTS
const byte ISS_Pin = 8;
const byte OSS_Pin = 9;
const byte LINE_PRESSURE_PIN = A7;
const byte EPC_PRESSURE_PIN = A6;

// OUTPUTS
const int TCC_PIN = 2; // make sure this is an analog pin
const int SOL_A_Pin = 4;
const int SOL_B_Pin = 3;
const int EPC_PIN = 5; // make sure this is an analog pin

// Constants
const int OSS_Holes = 12;
const double GearRatio = 4.56;
const double TireSize = 33;

const int ISS_Smoothing = 5;
const int OSS_Smoothing = 20;

// Variables
bool Load_Change = false; // not used except for testing? TODO
double Load_Avg = 0;
int LinePressure;
int EPCPressure;
int EPCPWM = 0;

double ISS[ISS_Smoothing];

int OSS[OSS_Smoothing];
double OSS_Speeds[OSS_Smoothing];
double OSS_Avg_Speed;
bool OSS_Speed_Change = false;
int OSS_Speed_Count = 0;
int OSS_Measure_Count = 0;
int OSSHigh = 0;

// possible overflow in 71.6 minutes. need to accomodate for reset.
// micros is for oss and
unsigned long OSS_Previous_Mircros;
unsigned long OSS_Current_Mircros;
unsigned long lastwritetime;

unsigned long Shift_Previous_Millis;
unsigned long Shift_Current_Millis;

// testing variables
bool enableEPC = true;
bool enabletcc = false;
bool enabletestshifting = false;
bool manualmode = 0;
bool loggingenabled = 1;
int cmd = -1;

// Timers
Timer ShiftingTimer(Shift);
Timer TCCTimer;

bool tccTimer = false;
bool shifting = false;
int CurrentGear = 0;

int CommandedGear = 1;
// int DesiredGear = 0; not needed?
#pragma endregion variables

void setup()
{
  pinMode(TCC_PIN, OUTPUT);
  pinMode(SOL_A_Pin, OUTPUT);
  pinMode(SOL_B_Pin, OUTPUT);
  pinMode(EPC_PIN, OUTPUT);

  pinMode(ISS_Pin, INPUT_PULLUP);
  pinMode(OSS_Pin, INPUT_PULLUP);
  pinMode(LINE_PRESSURE_PIN, INPUT);
  pinMode(EPC_PRESSURE_PIN, INPUT);

  // Can Bus stuff
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.begin(9600);
  Serial.println(VERSION);

  OSS_Previous_Mircros = micros();

  Shift();

  if (!verifycurves())
  {
    Serial.println("Error with shift curves. Halting execution.");
    while (1 == 2)
    {
      delay(1000);
    }
  }
}

void loop()
{
  // run the timers
  ShiftingTimer.Run();

  cmd = Serial.read();
  MeasurePressures();
  MeasureSpeed();
  RegulateEPC();
  CheckShift();

  if (cmd == 109) // m --toggle mode
    manualmode = !manualmode;

  if (manualmode)
  {
    switch (cmd)
    {
    case 49: // 1 --shift to 1st gear
    {
      CommandedGear = 1;
      break;
    }
    case 50: // 2 --shift to 2nd gear
    {
      CommandedGear = 2;
      ShiftingTimer.start(500, defaultcurves[FirstUP]);
      break;
    }
    case 51: // 3 --shift to 3rd gear
    {
      ShiftingTimer.start(500, defaultcurves[SecondUp]);
      CommandedGear = 3;
      break;
    }
    case 52: // 4 --shift to 4th gear
    {
      ShiftingTimer.start(500, defaultcurves[ThirdUp]);
      CommandedGear = 4;
      break;
    }
    case 48: // 0 --shift to imaginary 0th gear
    {
      CommandedGear = 0;
      break;
    }
    case 53: // 4 --shift to imaginary 5th gear
    {
      CommandedGear = 5;
      break;
    }
    case 54: // 6 --shift to imaginary 6th gear
    {
      CommandedGear = 6;
      break;
    }
    case 55: // 7 --shift to imaginary -1th gear
    {
      CommandedGear = -1;
      Shift();
      break;
    }
    case 101: // e --toggle epc
    {
      enableEPC = !enableEPC;

      // shutdown epc. should probably be a function
      EPCSetpoint = 0;
      analogWrite(EPC_PIN, EPCSetpoint);

      Serial.print("EPC = ");
      Serial.println(enableEPC);
      break;
    }
    case 116: // t --toggle torque converter TODO
    {
      enabletcc = !enabletcc;
      Serial.println("tcc is now ");
      Serial.println(enabletcc);
      if (enabletcc)
      {
        digitalWrite(TCC_PIN, HIGH);
      }
      else
      {
        digitalWrite(TCC_PIN, LOW);
      }

      break;
    }
    case 108: // l --increment fake load data
    {
      Load_Avg = Load_Avg + 3;
      Serial.print("Load is set to: ");
      Serial.println(Load_Avg);

      Load_Change = true;
      break;
    }
    case 76: // L --decrement fake load data
    {
      Load_Avg = Load_Avg - 3;
      Serial.print("Load is set to: ");
      Serial.println(Load_Avg);

      Load_Change = true;
      break;
    }
    case 99: // c --calc shift
    {
      CheckShift();
      break;
    }
    case 111: // o --increment OSS data
    {
      OSS_Avg_Speed;

      int newspeed = OSS_Avg_Speed + 3;
      if (newspeed > 130)
        newspeed = -20;
      for (int i = 0; i < OSS_Smoothing; i++)
      {
        OSS[i] = newspeed;
      }
      OSS_Avg_Speed = getAverage(OSS, OSS_Smoothing);
      Serial.print("Speed is set to: ");
      Serial.println(OSS_Avg_Speed);

      OSS_Speed_Change = true;
      break;
    }
    case 79: // O --decrement OSS data
    {
      OSS_Avg_Speed;

      int newspeed = OSS_Avg_Speed - 3;
      if (newspeed > 130)
        newspeed = -20;
      for (int i = 0; i < OSS_Smoothing; i++)
      {
        OSS[i] = newspeed;
      }
      OSS_Avg_Speed = getAverage(OSS, OSS_Smoothing);
      Serial.print("Speed is set to: ");
      Serial.println(OSS_Avg_Speed);

      OSS_Speed_Change = true;
      break;
    }
    case 65: // A --toggle shifting based on checkshift()
    {
      enabletestshifting = !enabletestshifting;
      Serial.print("debug shifting is currently: ");
      Serial.println(enabletestshifting);
      break;
    }
    case 118: // v --verify curves
    {
      if (verifycurves())
      {
        Serial.println("Shift curves good.");
      }
      else
      {
        Serial.println("Error with shift curves");
      }
      break;
    }
    case 43: // + --shift y int of curves up by 2
    {
      for (int i = 0; i < 6; i++)
        defaultcurves[i].y0 = defaultcurves[i].y0 + 2;

      Serial.println("curves shifted UP. verifying new curves");
      if (verifycurves())
        Serial.println("Shift curves good.");
      else
        Serial.println("Error with shift curves");

      break;
    }
    case 45: // -    -shift y int of curves down by 2
    {
      for (int i = 0; i < 6; i++)
        defaultcurves[i].y0 = defaultcurves[i].y0 - 2;

      Serial.println("curves shifted DOWN. verifying new curves");
      if (verifycurves())
        Serial.println("Shift curves good.");
      else
        Serial.println("Error with shift curves");

      break;
    }
    default: // command not found
    {
      if (cmd != -1)
      {
        Serial.println(cmd);
      }
      break;
    }
    }
    if (cmd != -1)
    {
      Serial.println("");
    }
    cmd = -1;
  }
  else
  {
    // TODO probably need to add this back in to main loop
    MeasureSpeed();
  }

  // TODO break this out into a function. inside getcanpacket it does global var stuff
  BroadcastPacket lol = GetCanPacket();
  if (lol.dataid == 1523)
  {
    Load_Avg = lol.tpsvalue;
  }
}

BroadcastPacket GetCanPacket()
{
  BroadcastPacket bptemp = {};
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    if (canMsg.can_id == 1523)
    {

      bptemp.dataid = canMsg.can_id;
      bptemp.tpsvalue = canMsg.data[1] | canMsg.data[0] << 8;
      bptemp.tpsvalue = bptemp.tpsvalue / 10;
    }
    // Serial.println(canMsg.can_id);
    if (canMsg.can_id == 1601)
    {
      manualmode = 1;
      if (canMsg.data[3])
      { // accel pin
        Serial.println("ACCEL detected!!");
        CommandedGear = CurrentGear + 1;
        if (CommandedGear = 5)
        {
          CommandedGear = 4;
        }
        Shift();
      }
      else if (canMsg.data[2])
      { // coast
        Serial.println("COAST detected!!");
        CommandedGear = CurrentGear - 1;
        if (CommandedGear = 0)
        {
          CommandedGear = 1;
        }
        Shift();
      }
      else if (canMsg.data[0])
      { // off
        Serial.println("OFF detected!!");
        EPCSetpoint = EPCSetpoint - 10;
      }
      else if (canMsg.data[1])
      { // on
        Serial.println("ON detected!!");
        EPCSetpoint = EPCSetpoint + 10;
      }
      else if (canMsg.data[4])
      { // TCC
        Serial.println("RES detected!!");
        enabletcc = !enabletcc;

        digitalWrite(TCC_PIN, enabletcc);
      }

      // send message
      canMsg1.can_id = 1602;
      canMsg1.can_dlc = 2;
      canMsg1.data[0] = CommandedGear;
      canMsg1.data[1] = enabletcc;
      mcp2515.sendMessage(&canMsg1);
    }
  }
  return bptemp;
}

void MeasureSpeed()
{
  OSS_Current_Mircros = micros();
  int reading = digitalRead(OSS_Pin);

  unsigned long timebetween;
  double hz;

  unsigned long duration = pulseIn(OSS_Pin, HIGH);
  float frequency = 1000000.0 / (2.0 * duration);

  // hz = (0.5 / timebetween) * 1000000;

  double s = 6.283185307 * (TireSize / 4.00) * (((frequency / OSS_Holes) * GearRatio) / 60) * .1;

  if (s < 140 and s > 0)
    OSS_Speeds[OSS_Speed_Count] = s;
  else
    OSS_Speeds[OSS_Speed_Count] = OSS_Avg_Speed;

  if (OSS_Speed_Count < OSS_Smoothing - 1)
    OSS_Speed_Count++;
  else
  {
    OSS_Speed_Count = 0;
  }

  double newspeed = getDoubleAverage(OSS_Speeds, OSS_Smoothing);
  if (int(newspeed) != int(OSS_Avg_Speed))
  {
    OSS_Speed_Change = true;
    OSS_Avg_Speed = newspeed;
  }
}

void RegulateEPC()
{
  if (enableEPC)
  {
    if (Load_Avg < 0)
    {
      Load_Avg = 0;
      if (loggingenabled)
      {
        Serial.println("RegulateEPC(): LOAD too LOW setting to 0 and continuing..");
      }
    }

    if (ShiftingTimer.isRunning)
    {
      EPCSetpoint = ShiftingTimer.ShiftCurve.PressureWhileShiftingSetpoint;
    }
    else
    {
      if (ShiftingTimer.ShiftCurve.PressureInGearSetpoint != 0)
      {
        EPCSetpoint = ShiftingTimer.ShiftCurve.PressureInGearSetpoint + Load_Avg;
      }
    }

    EPCPWM = 255 - pid.calculate(EPCSetpoint, EPCPressure);

    if (EPCPWM > 255)
    {
      EPCPWM = 255;
      if (loggingenabled)
      {
        Serial.print("epc pwm too HIGH setting to 255: ");
        Serial.println(EPCPWM);
      }
    }
    if (EPCPWM < 0)
    {
      EPCPWM = 0;
      if (loggingenabled)
      {
        Serial.print("epc pwm too LOW setting to 0: ");
        Serial.println(EPCPWM);
      }
    }

    // Serial.println(EPCSetpoint);
    analogWrite(EPC_PIN, EPCPWM);
    PrintInfo();
  }
}

void DetermineTCCLockup()
{
  // TCC_Current_Millis = millis();

  // if (TCC_Current_Millis - TCC_Previous_Millis > .25)
  //   waitingtcc = false;

  // TCC_Previous_Millis = TCC_Current_Millis;

  // // TODO make this a function of load_avg + temp + rpm
  // if (CurrentGear == 4 and Load_Avg < 0.75 and !shifting)
  // {
  //   analogWrite(TCC_PIN, TCC_Max);
  //   waitingtcc = true;
  // }
  // else
  analogWrite(TCC_PIN, 0);
}

void PrintInfo()
{
  if (millis() - lastwritetime > 500)
  {
    Serial.print("Data::");
    Serial.print("epcpwm:");
    Serial.print(EPCPWM);
    Serial.print(",epcpressuresetpoint:");
    Serial.print(EPCSetpoint);

    Serial.print(",load:");
    Serial.print(Load_Avg);

    Serial.print(",Line:");
    Serial.print(LinePressure);

    Serial.print(",EPC_Press:");
    Serial.print(EPCPressure);

    Serial.print(",tcc:");
    Serial.print(enabletcc);

    Serial.print(",CurrentGear:");
    Serial.print(CurrentGear);

    Serial.print(",CurrentSpeed:");
    Serial.println(OSS_Avg_Speed);
    lastwritetime = millis();
  }
}

void DumpInfo()
{
  Serial.println("Error: ");
  Serial.print("OSS 0:");
  Serial.println(OSS_Speeds[0]);
  Serial.print("OSS 1:");
  Serial.println(OSS_Speeds[1]);
  Serial.print("OSS 2:");
  Serial.println(OSS_Speeds[2]);
  Serial.print("OSS 3:");
  Serial.println(OSS_Speeds[3]);
  Serial.print("OSS 4:");
  Serial.println(OSS_Speeds[3]);

  Serial.println("");

  Serial.print("Average speed:");
  Serial.println(OSS_Avg_Speed);

  Serial.println("");

  Serial.print("prev micros:");
  Serial.println(OSS_Previous_Mircros);
  Serial.print("current micros:");
  Serial.println(OSS_Current_Mircros);

  Serial.println("");

  Serial.print("current gear:");
  Serial.println(CurrentGear);

  Serial.print("desired gear:");
  Serial.println(CalculateGear());
}

void CheckShift()
{
  if (!ShiftingTimer.isRunning)
  {
    CommandedGear = CalculateGear();
  }

  if (loggingenabled)
  {
    // Serial.print("CheckShift(): current/commanded: ");
    // Serial.print(CurrentGear);
    // Serial.print(",");
    // Serial.println(CommandedGear);
    // Serial.print("CheckShift(): speed/load: ");
    // Serial.print(OSS_Avg_Speed);
    // Serial.print(",");
    // Serial.println(Load_Avg);
  }
  if (CurrentGear != CommandedGear)
  {
    // Serial.print("gear: ");
    // Serial.print(CommandedGear);
    // Serial.print(",speed: ");
    // Serial.println(OSS_Avg_Speed);
  }
}

void MeasurePressures()
{
  //.29 is used to convert the 0-5v 0-300psi signal to 0-255
  LinePressure = analogRead(LINE_PRESSURE_PIN) * .29;
  EPCPressure = analogRead(EPC_PRESSURE_PIN) * .29;
}

void Shift()
{
  Serial.println("Shif()");

  // solenoid/clutch apply chart-----
  //  PRN1 1/0
  //  2 0/0
  //  3 0/1
  //  4 1/1

  // if (loggingenabled) {
  //   Serial.print("Shifting from ");
  //   Serial.print(CurrentGear);
  //   Serial.print(" to ");
  //   Serial.println(CommandedGear);
  // }

  // give tcc time to lock before shifting again?

  if (CurrentGear - CommandedGear > 1)
  {
    CommandedGear = CurrentGear - 1;
    if (loggingenabled)
    {
      Serial.println("current");
      Serial.println(CurrentGear);
      Serial.println("Error: skipping a DOWN shift gear.");
      Serial.print("New desired gear is: ");
      Serial.println(CommandedGear);
    }
  }

  if (CommandedGear - CurrentGear > 1)
  {
    CommandedGear = CurrentGear + 1;
    if (loggingenabled)
    {
      Serial.println("Error: skipping an UP shift gear.");
      Serial.print("New desired gear is: ");
      Serial.println(CommandedGear);
    }
  }

  if (CommandedGear > 4 || CommandedGear < 1)
  {
    if (loggingenabled)
    {
      Serial.print("Error: shifting to imaginary gear: ");
      Serial.println(CommandedGear);
      Serial.println("Canceling shift..");
    }
    CommandedGear = CurrentGear;
  }
  if (CommandedGear == CurrentGear)
  {
    if (loggingenabled)
      Serial.println("Error: shifting to same gear.");

    return;
    // return so we don't disable a locked tcc for no reason.
  }
  // disable tcc for smoother shift
  enabletcc = false;
  digitalWrite(TCC_PIN, 0);

  if (CommandedGear == 1)
  {
    digitalWrite(SOL_A_Pin, HIGH);
    digitalWrite(SOL_B_Pin, LOW);
    // Serial.println("here1");
    CurrentGear = 1;
  }
  else if (CommandedGear == 2)
  {
    digitalWrite(SOL_A_Pin, LOW);
    digitalWrite(SOL_B_Pin, LOW);
    // Serial.println("here2");
    CurrentGear = 2;
  }
  else if (CommandedGear == 3)
  {
    digitalWrite(SOL_A_Pin, LOW);
    digitalWrite(SOL_B_Pin, HIGH);
    // Serial.println("here3");
    CurrentGear = 3;
  }
  else if (CommandedGear == 4)
  {
    digitalWrite(SOL_A_Pin, HIGH);
    digitalWrite(SOL_B_Pin, HIGH);
    // Serial.println("here4");
    CurrentGear = 4;
  }
}

int CalculateGear()
{
  if (OSS_Avg_Speed < 0)
  {
    OSS_Avg_Speed = 0;

    if (loggingenabled)
      Serial.println("Speed < 0; setting to 0.");
  }

  if (OSS_Avg_Speed > 120)
  {
    OSS_Avg_Speed = 120;

    if (loggingenabled)
      Serial.println("Speed > 120; setting to 120.");
  }

  if (Load_Avg < 0)
  {
    Load_Avg = 0;

    if (loggingenabled)
      Serial.println("Load < 0; setting to 0.");
  }

  if (Load_Avg > 100)
  {
    Load_Avg = 100;

    if (loggingenabled)
      Serial.println("Speed > 100; setting to 100.");
  }

  if (CurrentGear == 1)
  {

    if (OSS_Avg_Speed > (CalcCurveValue(FirstUP, Load_Avg)))
    {
      ShiftingTimer.start(500, defaultcurves[FirstUP]);
      return 2;
    }
    else
    {
      return 1;
    }
  }
  else if (CurrentGear == 2)
  {
    if (OSS_Avg_Speed > (CalcCurveValue(SecondUp, Load_Avg)))
    {
      ShiftingTimer.start(500, defaultcurves[SecondUp]);
      return 3;
    }
    else if (OSS_Avg_Speed < (CalcCurveValue(SecondDown, Load_Avg)))
    {
      ShiftingTimer.start(500, defaultcurves[SecondDown]);
      return 1;
    }
    else
    {
      return 2;
    }
  }
  else if (CurrentGear == 3)
  {
    if (OSS_Avg_Speed > (CalcCurveValue(ThirdUp, Load_Avg)))
    {
      ShiftingTimer.start(500, defaultcurves[ThirdUp]);
      return 4;
    }
    else if (OSS_Avg_Speed < (CalcCurveValue(ThirdDown, Load_Avg)))
    {
      ShiftingTimer.start(500, defaultcurves[ThirdDown]);
      return 2;
    }
    else
    {
      return 3;
    }
  }
  else if (CurrentGear == 4)
  {
    if (OSS_Avg_Speed < (CalcCurveValue(FourthDown, Load_Avg)))
    {
      ShiftingTimer.start(500, defaultcurves[FourthDown]);
      return 3;
    }
    else
    {
      return 4;
    }
  }
  else
  {
    return 0;
  }
}

// Calulate the y value (speed) from the shift curves.
double CalcCurveValue(CurveName cname, double load)
{
  double m = (defaultcurves[cname].y100 - defaultcurves[cname].y0) / 100;

  int l2 = load / 10;
  // Serial.println("");
  // Serial.println(cname);
  // Serial.print("L2: ");
  // Serial.println(l2);
  
  double m2 = (bettercurves[cname].shiftpoints[l2 + 1] - bettercurves[cname].shiftpoints[l2]);
  // Serial.println(m2);

  //y = mx + b
  int b = bettercurves[cname].shiftpoints[l2] - l2*m2;
  // Serial.print("yint: ");
  // Serial.println(b);

  // Serial.print("curve val: ");
  // Serial.println((m * l2) + bettercurves[cname].shiftpoints[l2]);

  return (m * l2) + bettercurves[cname].shiftpoints[l2];
  //Serial.println(m2);
  //return (((m * load) + defaultcurves[cname].y0));
}

double getDoubleAverage(double arr[], int size)
{
  int i = 0;
  double sum = 0;
  double avg;

  for (i = 0; i < size; ++i)
  {
    sum += arr[i];
  }
  avg = sum / size;

  if (avg > 140)
  {
    Serial.println("error at getdoubleaverage()");
    DumpInfo();
    return OSS_Avg_Speed;
  }
  else
  {
    return avg;
  }
}

double getAverage(int arr[], int size)
{
  int i, sum = 0;
  double avg;

  for (i = 0; i < size; ++i)
  {
    sum += arr[i];
  }
  avg = double(sum) / size;
  if (avg > 140)
  {
    Serial.println("error at getAverage()");
    DumpInfo();
  }
  return avg;
}

bool verifycurves()
{
  // the previous upshift curve will always be above the next gears down shift
  // for example: 1 up has a higher y val than 2 down

  float prevslope = 0;
  for (Curve c : defaultcurves)
  {
    c.slope = (c.y100 - c.y0) / 100;

    if (loggingenabled)
    {
      Serial.print(c.curvename);
      Serial.print(",");
      Serial.print(c.y0);
      Serial.print(",");
      Serial.print(c.y100);
      Serial.print(",");
      Serial.println(c.slope);
    }

    if (c.slope < prevslope)
      return false;
  }

  if (defaultcurves[0].y0 < defaultcurves[1].y0)
    return false;
  if (defaultcurves[2].y0 < defaultcurves[3].y0)
    return false;
  if (defaultcurves[4].y0 < defaultcurves[5].y0)
    return false;

  if (defaultcurves[0].y0 > defaultcurves[2].y0)
    return false;
  if (defaultcurves[2].y0 > defaultcurves[4].y0)
    return false;

  return true;
}