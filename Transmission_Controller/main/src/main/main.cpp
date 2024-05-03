// https://wokwi.com/projects/new/arduino-uno
// https://ww2-secure.justanswer.com/uploads/bobover/2011-02-05_023022_line_pressure_test_4r70w.pdf

#include "main.h"

#ifdef TEST
MockSerial Serial;
#endif

const String VERSION = "02.22.24.1";
// const bool ENABLE_CAN_BUS;
// int count = 11;

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
  int tpsValue;
  // int dataid = 1523;  //this is the id of the realtime data broadcasting packet
  int dataid = -13;
  int other1;
  int other2;
  int other3;
};

BroadcastPacket bp = {};

enum ShiftMode
{
  Manual = 0,
  ManualTow = 1,
  Auto = 2,
  Performance = 3,
  RPMBased = 4
};

Curve bettercurves[6] = {
    {FirstUP, {3, 3, 3, 4, 4, 4, 6, 7, 11, 17, 28}, {10, 10, 10, 10, 10, 20, 20, 20, 30, 30, 40}, 40, 1},
    {SecondDown, {1, 1, 1, 2, 2, 2, 2, 2, 3, 6, 12}, {10, 10, 10, 10, 10, 20, 20, 20, 30, 30, 40}, 40, 1},
    {SecondUp, {14, 11, 12, 15, 21, 27, 33, 40, 48, 58, 68}, {10, 10, 12, 15, 21, 27, 33, 40, 48, 58, 68}, 40, 1},
    {ThirdDown, {8, 8, 9, 9, 9, 11, 13, 15, 20, 28, 47}, {8, 8, 9, 9, 9, 11, 13, 15, 20, 28, 47}, 40, 1},
    {ThirdUp, {30, 29, 31, 41, 51, 60, 75, 85, 93, 100, 100}, {27, 28, 31, 31, 35, 42, 50, 60, 70, 80, 90}, 50, 1},
    {FourthDown, {20, 20, 23, 30, 39, 47, 55, 60, 66, 74, 79}, {20, 20, 23, 30, 39, 47, 55, 60, 66, 74, 79}, 50, 1}};


PID inGearPID(.25, 0.2, 0.2);
PID shiftingPID(1, 1, 1);

int EPCSetpoint = 30;

// INPUTS
const byte ISS_Pin = 8;
const byte OSS_Pin = 9;
const byte Fuel_Level_Pin = A8;
const byte OIL_Pressure_PIN = A5;
const byte EPC_PRESSURE_PIN = A6;

// OUTPUTS
const int TCC_PIN = 2; // make sure this is an analog pin
const int SOL_A_Pin = 4;
const int SOL_B_Pin = 3;
const int EPC_PIN = 5; // make sure this is an analog pin

// Constants
const int OSS_Holes = 2;
const int ISS_Holes = 12;
const double GearRatio = 4.56;
const double TireSize = 33;

const int ISS_Smoothing = 10;
const int OSS_Smoothing = 50;

// Variables
double Load_Avg = 0;
int FuelLevel;
int OilPressure;
int EPCPressure;
int EPCPWM = 0;
int rpmValue;

int ISS[ISS_Smoothing];
int OSS[OSS_Smoothing];
int OSS_Speeds[OSS_Smoothing];
double ISS_Speeds[ISS_Smoothing];
double OSS_Avg_Speed;
double ISS_Avg_Speed;
int OSS_Speed_Count = 0;
int ISS_Speed_Count = 0;
int OSS_Measure_Count = 0;
int ISS_Measure_Count = 0;
int OSSHigh = 0;
int ISSHigh = 0;

float trans_Slippage = 0.00;

// possible overflow in 71.6 minutes. need to accomodate for reset.
// micros is for oss and
unsigned long OSS_Previous_Mircros;
unsigned long OSS_Current_Mircros;
unsigned long ISS_Current_Mircros;
unsigned long lastwritetime;

unsigned long Shift_Previous_Millis;
unsigned long Shift_Current_Millis;

// testing variables
bool enableEPC = true;
bool enabletcc = false;
bool enabletestshifting = false;
int ShiftMode = Manual;

bool loggingenabled = 1;
int cmd = -1;

// Timers
ShiftingTimer shiftingTimer(Shift);
Timer postShiftTimer(2000);
// Timer tccTimer(Lockup);

bool tccTimer = false;
bool shifting = false;
int CurrentGear = 0;

int CommandedGear = 1;
// int DesiredGear = 0; not needed?
#pragma endregion variables

void arduinosetup()
{
  pinMode(TCC_PIN, OUTPUT);
  pinMode(SOL_A_Pin, OUTPUT);
  pinMode(SOL_B_Pin, OUTPUT);
  pinMode(EPC_PIN, OUTPUT);

  pinMode(ISS_Pin, INPUT_PULLUP);
  pinMode(OSS_Pin, INPUT_PULLUP);
  pinMode(Fuel_Level_Pin, INPUT);
  pinMode(OIL_Pressure_PIN, INPUT);
  pinMode(EPC_PRESSURE_PIN, INPUT);

  // Can Bus stuff
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.begin(9600);
  Serial.println(VERSION);

  OSS_Previous_Mircros = micros();

  Shift();
}

void arduinoloop()
{
  // run the timers
  shiftingTimer.Run();
  postShiftTimer.Run();

  MeasurePressures();

  MeasureSpeed();

  RegulateEPC();

  cmd = Serial.read();

  if (cmd == 109) // m --toggle mode
    ShiftMode = Manual;

  if (ShiftMode == Manual)
  {
    ManualMode();
  }
  else
  {
    CheckShift();

    TCCLockup();
  }

  // TODO break this out into a function. inside getcanpacket it does global var stuff
  // BroadcastPacket lol = GetCanPacket();
  while (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    if (canMsg.can_id == 1523)
    {
      Load_Avg = canMsg.data[1] | canMsg.data[0] << 8;
      Load_Avg = Load_Avg / 10;
    }
    else if (canMsg.can_id == 1520)
    {
      rpmValue = canMsg.data[7] | canMsg.data[6] << 8;
    }
    else if (canMsg.can_id == 1601 && !shiftingTimer.isRunning && !postShiftTimer.isRunning)
    {
      ShiftMode = Manual;
      if (canMsg.data[3])
      { // accel pin
        Serial.println("ACCEL detected!!");
        CommandedGear = CurrentGear + 1;
        if (CommandedGear = 5)
        {
          CommandedGear = 4;
        }

        switch (CommandedGear)
        {
        case 2:
          // 1->2 FirstUP = 0,
          shiftingTimer.start(500, bettercurves[FirstUP]);
          break;
        case 3:
          // 2->3 SecondUp = 2,
          shiftingTimer.start(500, bettercurves[SecondUp]);
          break;
        case 4:
          // 3->4 ThirdUp = 4,
          shiftingTimer.start(500, bettercurves[ThirdUp]);
          break;
        default:
          break;
        }
      }
      else if (canMsg.data[2])
      { // coast
        Serial.println("COAST detected!!");
        CommandedGear = CurrentGear - 1;
        if (CommandedGear == 0)
        {
          CommandedGear = 1;
        }

        switch (CommandedGear)
        {
        case 1:
          // 2->1
          shiftingTimer.start(500, bettercurves[SecondDown]);
          break;
        case 2:
          // 3->2
          shiftingTimer.start(500, bettercurves[ThirdDown]);
          break;
        case 3:
          // 4->3
          shiftingTimer.start(500, bettercurves[FourthDown]);
          break;
        default:
          break;
        }
      }
      else if (canMsg.data[0])
      { // off
        Serial.println("OFF detected!!");
      }
      else if (canMsg.data[1])
      { // on
        Serial.println("ON detected!!");
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
  SendCanData();

  // PrintSerialData();
}

void MeasureSpeed()
{
  unsigned long duration = pulseIn(OSS_Pin, HIGH);
  int s;
  if (duration > 0)
  {
    float frequency = 1000000.0 / (1.0 * duration);
    s = 6.283185307 * (TireSize / 4.00) * (((frequency / OSS_Holes) * GearRatio) / 60) * .1;
  }
  else
  {
    s = 0;
  }

  if (s < 140 && s > -1)
    OSS_Speeds[OSS_Speed_Count] = s;
  else
    OSS_Speeds[OSS_Speed_Count] = OSS_Avg_Speed;

  if (OSS_Speed_Count < OSS_Smoothing - 1)
    OSS_Speed_Count++;
  else
  {
    // for (int i = 0; i < OSS_Smoothing; i++)
    // {
    //   Serial.print(OSS_Speeds[i]);
    //   Serial.print(",");
    // }
    // Serial.println("");
    OSS_Speed_Count = 0;
  }

  double newspeed = getDoubleAverageWithoutExtremeValues(OSS_Speeds, OSS_Smoothing);
  OSS_Avg_Speed = newspeed;
}

void MeasureISS()
{
  unsigned long duration = pulseIn(ISS_Pin, HIGH);
  double s;
  float frequency = 1000000.0 / (1.0 * duration);
  if (duration > 0)
  {
    s = 6.283185307 * (TireSize / 4.00) * (((frequency / ISS_Holes) * GearRatio) / 60) * .1;
  }
  else
  {
    s = 0;
  }

  if (s < 140 && s > 0)
    ISS_Speeds[ISS_Speed_Count] = s;
  else
    ISS_Speeds[ISS_Speed_Count] = ISS_Avg_Speed;

  if (ISS_Speed_Count < ISS_Smoothing - 1)
    ISS_Speed_Count++;
  else
  {
    ISS_Speed_Count = 0;
  }

  double newspeed = getDoubleAverage(ISS_Speeds, ISS_Smoothing);
  ISS_Avg_Speed = newspeed;
}

void RegulateEPC()
{
  int PreviousEPCPWM = EPCPWM;
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

    if (shiftingTimer.isRunning)
    {
      EPCSetpoint = CalcPressureValue(shiftingTimer.ShiftCurve, Load_Avg);
      EPCPWM = 120 - shiftingPID.calculate(EPCSetpoint, EPCPressure);
    }
    else
    {
      EPCSetpoint = shiftingTimer.ShiftCurve.PressureInGearSetpoint;
      EPCPWM = 80 - inGearPID.calculate(EPCSetpoint, EPCPressure);
    }

    EPCPWM = constrain(EPCPWM, 0, 255);

    if (PreviousEPCPWM != EPCPWM)
    {
      analogWrite(EPC_PIN, EPCPWM);
    }
  }
}

void TCCLockup()
{
  if (shiftingTimer.isRunning || postShiftTimer.isRunning)
  {
    enabletcc = false;
  }
  else
  {
    if (CurrentGear == 4 && OSS_Avg_Speed > 50)
    {
      enabletcc = true;
    }
    else
    {
      enabletcc = false;
    }
  }
  digitalWrite(TCC_PIN, enabletcc);
}

void SendCanData()
{
  if (millis() - lastwritetime > 200)
  {
    struct can_frame canMsg2;
    canMsg2.can_id = 1702;
    canMsg2.can_dlc = 4;
    canMsg2.data[0] = constrain(enabletcc, 0, 1);
    canMsg2.data[1] = constrain(CurrentGear, 0, 12);
    canMsg2.data[2] = constrain(OSS_Avg_Speed, 0, 255);
    canMsg2.data[3] = constrain(OilPressure, 0, 255);
    mcp2515.sendMessage(&canMsg2);

    struct can_frame canMsg3;
    canMsg3.can_id = 1802;
    canMsg3.can_dlc = 8;
    canMsg3.data[0] = ShiftMode;
    canMsg3.data[1] = 0; // empty was line pressure

    canMsg3.data[2] = (EPCPressure >> 8) & 0xFF;
    canMsg3.data[3] = EPCPressure & 0xFF;

    canMsg3.data[4] = constrain(EPCPWM, 0, 255);
    canMsg3.data[5] = constrain(EPCSetpoint, 0, 255);
    canMsg3.data[6] = constrain(ISS_Avg_Speed, 0, 255);
    canMsg3.data[7] = constrain(FuelLevel / 4.01, 0, 255);
    mcp2515.sendMessage(&canMsg3);
    lastwritetime = millis();
  }
}

void PrintSerialData()
{
  Serial.print("Data::");

  Serial.print("Time:");
  Serial.print(millis());

  Serial.print(",epcpwm:");
  Serial.print(EPCPWM);
  Serial.print(",epcpressuresetpoint:");
  Serial.print(EPCSetpoint);

  Serial.print(",load:");
  Serial.print(Load_Avg);

  Serial.print(",EPC_Press:");
  Serial.print(EPCPressure);

  Serial.print(",ISS_Speed:");
  Serial.print(ISS_Avg_Speed);

  Serial.print(",Slippage:");
  Serial.print(trans_Slippage);

  Serial.print(",tcc:");
  Serial.print(enabletcc);

  Serial.print(",rpm:");
  Serial.print(rpmValue);

  Serial.print(",CurrentGear:");
  Serial.print(CurrentGear);

  Serial.print(",CurrentSpeed:");
  Serial.println(OSS_Avg_Speed);
}

void splitIntoTwoBytes(int value, byte &byte1, byte &byte2)
{
  byte1 = (value >> 8) & 0xFF;
  byte2 = value & 0xFF;
  return;
}

void CheckShift()
{
  if (!shiftingTimer.isRunning && !postShiftTimer.isRunning)
  {
    CommandedGear = CalculateGear();
  }
}

void MeasurePressures()
{
  // scale is based off of 635 = full and 573 = full-3.73 gallons (87%)
  FuelLevel = (analogRead(Fuel_Level_Pin) * 0.209) - 32.45;

  //.367 is used to convert the 0.5-4.5v 0-1024 value signal to 0-300psi
  //.184 for 0-1024 to 0-150psi
  // 102 is the .5v offset
  OilPressure = (analogRead(OIL_Pressure_PIN) - 102) * 0.184;
  EPCPressure = (analogRead(EPC_PRESSURE_PIN) - 102) * 0.367;
  EPCPressure = constrain(EPCPressure, 0, 300);
  OilPressure = constrain(OilPressure, 0, 150);
}

void Shift()
{
  // solenoid/clutch apply chart-----
  //  PRN1 1/0
  //  2 0/0
  //  3 0/1
  //  4 1/1

  // clear the pid error and output
  inGearPID.clear();
  shiftingPID.clear();

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
    CurrentGear = 1;
  }
  else if (CommandedGear == 2)
  {
    digitalWrite(SOL_A_Pin, LOW);
    digitalWrite(SOL_B_Pin, LOW);
    CurrentGear = 2;
  }
  else if (CommandedGear == 3)
  {
    digitalWrite(SOL_A_Pin, LOW);
    digitalWrite(SOL_B_Pin, HIGH);
    CurrentGear = 3;
  }
  else if (CommandedGear == 4)
  {
    digitalWrite(SOL_A_Pin, HIGH);
    digitalWrite(SOL_B_Pin, HIGH);
    CurrentGear = 4;
  }
  postShiftTimer.start(1000);
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
    if (OSS_Avg_Speed > (CalcShiftValue(FirstUP, Load_Avg)))
    {
      shiftingTimer.start(500, bettercurves[FirstUP]);
      return 2;
    }
    else
    {
      return 1;
    }
  }
  else if (CurrentGear == 2)
  {
    if (OSS_Avg_Speed > (CalcShiftValue(SecondUp, Load_Avg)))
    {
      shiftingTimer.start(500, bettercurves[SecondUp]);
      return 3;
    }
    else if (OSS_Avg_Speed < (CalcShiftValue(SecondDown, Load_Avg)))
    {
      shiftingTimer.start(500, bettercurves[SecondDown]);
      return 1;
    }
    else
    {
      return 2;
    }
  }
  else if (CurrentGear == 3)
  {
    if (OSS_Avg_Speed > (CalcShiftValue(ThirdUp, Load_Avg)))
    {
      shiftingTimer.start(500, bettercurves[ThirdUp]);
      return 4;
    }
    else if (OSS_Avg_Speed < (CalcShiftValue(ThirdDown, Load_Avg)))
    {
      shiftingTimer.start(500, bettercurves[ThirdDown]);
      return 2;
    }
    else
    {
      return 3;
    }
  }
  else if (CurrentGear == 4)
  {
    if (OSS_Avg_Speed < (CalcShiftValue(FourthDown, Load_Avg)))
    {
      shiftingTimer.start(500, bettercurves[FourthDown]);
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
double CalcShiftValue(int cname, double load)
{
 //bettercurves[cname].shiftPoints = [3, 3, 3, 4, 4, 4, 6, 7, 11, 17, 28]

  load = constrain(load,0,100);
  int l2 = load / 10;
  double dif = (bettercurves[cname].shiftPoints[l2 + 1] - bettercurves[cname].shiftPoints[l2]); 
  double m2 = dif /10;
  double b = double(bettercurves[cname].shiftPoints[l2]) - m2 * l2*10;
  return double(m2 * load + b);
}

double CalcPressureValue(Curve curve, double load)
{
  load = constrain(load,0,100);
  int l2 = load / 10;
  double dif = (curve.pressurePoints[l2 + 1] - curve.pressurePoints[l2]);
  double m2 = dif / 10;
  double b = double(curve.pressurePoints[l2]) - m2 * l2*10;
  return double(m2 * load + b);
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
  return avg;
}

int getDoubleAverageWithoutExtremeValues(int arr[], int size)
{
  int sum = 0;
  for (int i = 0; i < size; ++i)
  {
    sum += arr[i];
  }
  double mean = sum / size;

  double sq_diff_sum = 0;
  for (int i = 0; i < size; ++i)
  {
    sq_diff_sum += (arr[i] - mean) * (arr[i] - mean);
  }
  double std_dev = sqrt(sq_diff_sum / size);

  double lowerBound = mean - 2 * std_dev;
  double upperBound = mean + 2 * std_dev;

  sum = 0;
  int count = 0;
  for (int i = 0; i < size; ++i)
  {
    if (arr[i] >= lowerBound && arr[i] <= upperBound)
    {
      sum += arr[i];
      ++count;
    }
  }

  return count == 0 ? 0 : sum / count;
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
  }
  return avg;
}

void ManualMode()
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
    shiftingTimer.start(500, bettercurves[FirstUP]);
    break;
  }
  case 51: // 3 --shift to 3rd gear
  {
    shiftingTimer.start(500, bettercurves[SecondUp]);
    CommandedGear = 3;
    break;
  }
  case 52: // 4 --shift to 4th gear
  {
    shiftingTimer.start(500, bettercurves[ThirdUp]);
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
    break;
  }
  case 76: // L --decrement fake load data
  {
    Load_Avg = Load_Avg - 3;
    Serial.print("Load is set to: ");
    Serial.println(Load_Avg);
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

    break;
  }
  case 65: // A --toggle shifting based on checkshift()
  {
    enabletestshifting = !enabletestshifting;
    Serial.print("debug shifting is currently: ");
    Serial.println(enabletestshifting);
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