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

// EPC
// Line Pressure = 0.389x +56.1
// 290hz?
#pragma endregion notes

#pragma region variables
// INPUTS
const byte Load_Pin = A4;
const byte ISS_Pin = 3;
const byte OSS_Pin = 2;
const byte LinePressure_Pin = A1;
const byte EPCPressure_Pin = A0;

// OUTPUTS
int TCC_Pin = 9; // make sure this is an analog pin
int SolA_Pin = 10;
int SolB_Pin = 11;
int EPC_Pin = 6; // make sure this is an analog pin

// Constants
const int OSS_Holes = 12;
const double GearRatio = 3.55;
const double TireSize = 33;

const int TCC_Max = 0.75 * 255;
const int TCC_Min = 0.3 * 255;
const double TCC_Seconds_Before = .1;

const int Load_Smoothing = 5;
const int ISS_Smoothing = 5;
const int OSS_Smoothing = 5;

// Variables
double Load[Load_Smoothing];
int Load_Measure_count = 0;
double Load_Avg = 0;

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

unsigned long Load_Previous_Millis;
unsigned long Load_Current_Millis;

unsigned long Shift_Previous_Millis;
unsigned long Shift_Current_Millis;

unsigned long TCC_Previous_Millis;
unsigned long TCC_Current_Millis;

// testing variables
bool enableEPC = false;
bool manualmode = 1;
bool loggingenabled = 1;
int cmd = -1;

bool waitingtcc = false;
bool shifting = false;
int CurrentGear = 1;
int EPCPWM = 0;
int WantedGear = 1;
// int DesiredGear = 0; not needed?
#pragma endregion variables

void setup()
{
#pragma region PinStates
  pinMode(TCC_Pin, OUTPUT);
  pinMode(SolA_Pin, OUTPUT);
  pinMode(SolB_Pin, OUTPUT);
  pinMode(EPC_Pin, OUTPUT);

  pinMode(Load_Pin, INPUT);
  pinMode(ISS_Pin, INPUT);
  pinMode(OSS_Pin, INPUT);
  pinMode(LinePressure_Pin, INPUT);
  pinMode(EPCPressure_Pin, INPUT);

  pinMode(13, OUTPUT);

// RE-ENABLE THIS WHEN YOU ARE READY TO DRIVE!!!!-----------
// prepare outputs for vehicle startup
// analogWrite(EPC_Pin, EPC_Max);
// analogWrite(TCC_Pin, TCC_Max);
// digitalWrite(SolA_Pin, HIGH);
// digitalWrite(SolA_Pin, LOW);
#pragma endregion PinStates

  OSS_Previous_Mircros = micros();
  Load_Previous_Millis = millis();
  Serial.begin(9600);

  // analogtest();
  // digitaltest();
}

void loop()
{
  cmd = Serial.read();

  if (cmd == 109) // m --toggle mode
    manualmode = !manualmode;

  if (manualmode)
  {
    switch (cmd)
    {
    case 49: // 1 --shift to 1st gear
    {
      WantedGear = 1;
      Shift();
      break;
    }
    case 50: // 2 --shift to 2nd gear
    {
      WantedGear = 2;
      Shift();
      break;
    }
    case 51: // 3 --shift to 3rd gear
    {
      WantedGear = 3;
      Shift();
      break;
    }
    case 52: // 4 --shift to 4th gear
    {
      WantedGear = 4;
      Shift();
      break;
    }
    case 48: // 0 --shift to imaginary 0th gear
    {
      WantedGear = 0;
      Shift();
      break;
    }
    case 53: // 4 --shift to imaginary 5th gear
    {
      WantedGear = 5;
      Shift();
      break;
    }
    case 54: // 6 --shift to imaginary 6th gear
    {
      WantedGear = 6;
      Shift();
      break;
    }
    case 55: // 7 --shift to imaginary -1th gear
    {
      WantedGear = -1;
      Shift();
      break;
    }
    case 101: // e --toggle epc
    {
      enableEPC = !enableEPC;
      Serial.print("EPC = ");
      Serial.println(enableEPC);
      break;
    }
    case 116: // t --toggle torque converter TODO
    {
      Serial.println("not implemented");
      break;
    }
    case 108: // l --increment fake load data
    {
      int newload = Load_Avg + 10;
      if (newload > 130)
        newload = -20;
      for (int i = 0; i < Load_Smoothing; i++)
      {
        Load[i] = newload;
      }
      Load_Avg = getDoubleAverage(Load, Load_Smoothing);
      Serial.print("Load is set to: ");
      Serial.println(Load_Avg);
      break;
    }
    case 99: // c --calc shift
    {
      break;
    }
    case 115: // s --increment fake speed data
    {
      break;
    }
    case 111: // o --increment OSS data
    {
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

    cmd = -1;

    if (enableEPC)
    {
      RegulateEPC();
    }
  }
  else
  {
    MeasureLoad();
    MeasureSpeed();

    RegulateEPC();

    if (OSS_Speed_Change)
      CheckShift();
    // else
    //   DumpInfo();

    // DetermineTCCLockup(); TODO

    if (WantedGear != CurrentGear)
      Shift();
  }
}

void MeasureSpeed()
{
  OSS_Current_Mircros = micros();
  OSS[OSS_Measure_Count] = digitalRead(OSS_Pin);
  OSS_Measure_Count++;
  // bool HasChanged = false; not needed?
  unsigned long timebetween;
  double hz;
  // reset array

  if (OSS_Measure_Count == OSS_Smoothing)
    OSS_Measure_Count = 0;

  double ossavg = getAverage(OSS, OSS_Smoothing);

  if (ossavg > (2.0 / OSS_Smoothing) and OSSHigh == 0)
  {
    OSSHigh = 1;
    digitalWrite(13, HIGH);
    timebetween = OSS_Current_Mircros - OSS_Previous_Mircros;
    hz = (1.00 / timebetween) * 1000000;
    double s = 6.283185307 * (TireSize / 2.00) * (((hz / OSS_Holes) * GearRatio) / 60);

    if (s < 140 and s > 0)
      OSS_Speeds[OSS_Speed_Count] = s;
    else
      OSS_Speeds[OSS_Speed_Count] = ossavg;

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
    }
    else
    {
      OSS_Speed_Change = false;
    }
    OSS_Avg_Speed = newspeed;
  }

  if (ossavg < (2.0 / OSS_Smoothing) and OSSHigh == 1)
  {
    OSSHigh = 0;
    digitalWrite(13, LOW);
    OSS_Previous_Mircros = OSS_Current_Mircros;
  }
}

void MeasureLoad()
{
  Load_Current_Millis = millis();
  // measure every .1 seconds
  if (Load_Current_Millis > Load_Previous_Millis + 100)
  {
    Load[Load_Measure_count] = analogRead(Load_Pin) / 255;
    Load[Load_Measure_count]++;
  }

  if (Load_Measure_count == Load_Smoothing)
    Load_Measure_count = 0;

  Load_Avg = getDoubleAverage(Load, Load_Smoothing);

  Load_Previous_Millis = Load_Current_Millis;
}

void RegulateEPC()
{
  // 0.4x + 56
  int EPCPWM_temp = ((0.4 * Load_Avg) + 60) * 2.55;

  if (EPCPWM_temp > 255)
  {
    EPCPWM_temp = 255;
    if (loggingenabled)
    {
      Serial.print("epc pwm too HIGH setting to 255: ");
      Serial.println(EPCPWM);
    }
  }

  if (EPCPWM_temp < 0)
  {
    EPCPWM_temp = 0;
    if (loggingenabled)
    {
      Serial.print("epc pwm too LOW setting to 0: ");
      Serial.println(EPCPWM);
    }
  }

  // 5 is a random sensitivity number.
  int triggerdelta = 5;
  if (abs(EPCPWM - EPCPWM_temp) > triggerdelta)
  {
    analogWrite(EPC_Pin, EPCPWM_temp);
    EPCPWM = EPCPWM_temp;
    if (loggingenabled)
    {
      Serial.print("epc pwm set to: ");
      Serial.println(EPCPWM);
    }
  }
  else
  {
    if (loggingenabled && 1 == 2) // disabled to skip repeated messages
    {
      Serial.print("skipping epc change because diff <  ");
      Serial.println(triggerdelta);
    }
  }
}

void DetermineTCCLockup()
{
  TCC_Current_Millis = millis();

  if (TCC_Current_Millis - TCC_Previous_Millis > .25)
    waitingtcc = false;

  TCC_Previous_Millis = TCC_Current_Millis;

  // TODO make this a function of load_avg + temp + rpm
  if (CurrentGear == 4 and Load_Avg < 0.75 and !shifting)
  {
    analogWrite(TCC_Pin, TCC_Max);
    waitingtcc = true;
  }
  else
    analogWrite(TCC_Pin, 0);
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
  Serial.println(DesiredGear());
}

void CheckShift()
{
  WantedGear = DesiredGear();
  if (CurrentGear != WantedGear)
  {
    Serial.print("gear: ");
    Serial.print(WantedGear);
    Serial.print(",speed: ");
    Serial.println(OSS_Avg_Speed);
  }
}

void Shift()
{
  // solenoid/clutch apply chart-----
  //  PRN1 1/0
  //  2 0/0
  //  3 0/1
  //  4 1/1

  if (loggingenabled)
  {
    Serial.print("Shifting from ");
    Serial.print(CurrentGear);
    Serial.print(" to ");
    Serial.println(WantedGear);
  }

  // give tcc time to lock before shifting again?
  Shift_Current_Millis = millis();
  if (Shift_Current_Millis - Shift_Previous_Millis > .1)
  {
    shifting = false;
  }

  shifting = true;
  Shift_Previous_Millis = Shift_Current_Millis;

#pragma region Shifting logic sanity check
  if (CurrentGear - WantedGear > 1)
  {
    WantedGear = CurrentGear - 1;
    if (loggingenabled)
    {
      Serial.println("Error: skipping a DOWN shift gear.");
      Serial.print("New desired gear is: ");
      Serial.println(WantedGear);
    }
  }

  if (WantedGear - CurrentGear > 1)
  {
    WantedGear = CurrentGear + 1;
    if (loggingenabled)
    {
      Serial.println("Error: skipping an UP shift gear.");
      Serial.print("New desired gear is: ");
      Serial.println(WantedGear);
    }
  }

  if (WantedGear == CurrentGear)
  {
    if (loggingenabled)
      Serial.println("Error: shifting to same gear.");
    return;
  }

  if (WantedGear > 4 || WantedGear < 1)
  {
    if (loggingenabled)
    {
      Serial.print("Error: shifting to imaginary gear: ");
      Serial.println(WantedGear);
      Serial.println("Canceling shift..");
    }
    WantedGear = CurrentGear;
    return;
  }
#pragma endregion

  if (WantedGear == 1)
  {
    digitalWrite(SolA_Pin, HIGH);
    digitalWrite(SolB_Pin, LOW);
    CurrentGear = 1;
  }
  else if (WantedGear == 2)
  {
    digitalWrite(SolA_Pin, LOW);
    digitalWrite(SolB_Pin, LOW);
    CurrentGear = 2;
  }
  else if (WantedGear == 3)
  {
    digitalWrite(SolA_Pin, LOW);
    digitalWrite(SolB_Pin, HIGH);
    CurrentGear = 3;
  }
  else if (WantedGear == 4)
  {
    digitalWrite(SolA_Pin, HIGH);
    digitalWrite(SolB_Pin, HIGH);
    CurrentGear = 4;
  }
}

int DesiredGear()
{
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

  double Load_Avg = 25;

  if (CurrentGear == 1)
  {
    if (OSS_Avg_Speed > (Load_Avg * 0.389 + 5.11))
    {
      return 2;
    }
    else
    {
      return 1;
    }
  }
  else if (CurrentGear == 2)
  {
    if (OSS_Avg_Speed > (Load_Avg * 0.778 + 10.2))
    {
      return 3;
    }
    else if (OSS_Avg_Speed < (Load_Avg * 0.333 + 3.67))
    {
      return 1;
    }
    else
    {
      return 2;
    }
  }
  else if (CurrentGear == 3)
  {
    if (OSS_Avg_Speed > (Load_Avg * 1.17 + 14.3))
    {
      return 4;
    }
    else if (OSS_Avg_Speed < (Load_Avg * 0.722 + 8.78))
    {
      return 2;
    }
    else
    {
      return 3;
    }
  }
  else if (CurrentGear == 4)
  {
    if (OSS_Avg_Speed < (Load_Avg * 1.06 + 13.4))
    {
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

void digitaltest()
{

  digitalWrite(EPC_Pin, HIGH);
  delay(1000);
  digitalWrite(EPC_Pin, LOW);

  delay(1000);
  digitalWrite(SolA_Pin, HIGH);
  delay(1000);
  digitalWrite(SolA_Pin, LOW);

  delay(1000);
  digitalWrite(SolB_Pin, HIGH);
  delay(1000);
  digitalWrite(SolB_Pin, LOW);

  delay(1000);
  digitalWrite(TCC_Pin, HIGH);
  delay(1000);
  digitalWrite(TCC_Pin, LOW);
}

void analogtest()
{

  delay(1000);
  analogWrite(TCC_Pin, 50);
  delay(1000);
  analogWrite(TCC_Pin, 100);
  delay(1000);
  analogWrite(TCC_Pin, 150);
  delay(1000);
  analogWrite(TCC_Pin, 200);
  delay(1000);
  analogWrite(TCC_Pin, 250);
  delay(1000);
  analogWrite(TCC_Pin, 0);

  delay(1000);
  analogWrite(EPC_Pin, 50);
  delay(1000);
  analogWrite(EPC_Pin, 100);
  delay(1000);
  analogWrite(EPC_Pin, 150);
  delay(1000);
  analogWrite(EPC_Pin, 200);
  delay(1000);
  analogWrite(EPC_Pin, 250);
  delay(1000);
  analogWrite(EPC_Pin, 0);

  delay(1000);
  analogWrite(SolA_Pin, 50);
  delay(1000);
  analogWrite(SolA_Pin, 100);
  delay(1000);
  analogWrite(SolA_Pin, 150);
  delay(1000);
  analogWrite(SolA_Pin, 200);
  delay(1000);
  analogWrite(SolA_Pin, 250);
  delay(1000);
  analogWrite(SolA_Pin, 0);

  delay(1000);
  analogWrite(SolB_Pin, 50);
  delay(1000);
  analogWrite(SolB_Pin, 100);
  delay(1000);
  analogWrite(SolB_Pin, 150);
  delay(1000);
  analogWrite(SolB_Pin, 200);
  delay(1000);
  analogWrite(SolB_Pin, 250);
  delay(1000);
  analogWrite(SolB_Pin, 0);
}
