#pragma region notes
// solenoid/clutch apply chart-----
//  PRN1 1/0
//  2 0/0
//  3 0/1
//  4 1/1

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

// TODO
// tcc unlock = 20%
// tcc lockup time 3 seconds 30%-70%
// tcc unlock on throttle off?
// unlock tcc as you shift?
// rolling start?
// time overflow

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
const int EPC_Max = 0.75 * 255;
const int EPC_Min = 0.3 * 255;
const int Load_Smoothing = 1;
const int ISS_Smoothing = 5;
const int OSS_Smoothing = 5;

// Variables
int Load[Load_Smoothing];
// int LoadHigh = 0; not needed?

int ISS[ISS_Smoothing];
// int ISSHigh = 0; not needed?

int OSS[OSS_Smoothing];
double OSS_Speeds[OSS_Smoothing];
double OSS_Avg_Speed;
bool OSS_Speed_Change = false;
int OSS_Speed_Count = 0;
int OSS_Measure_Count = 0;
int OSSHigh = 0;

// possible overflow in 71.6 minutes. need to accomodate for reset.
unsigned long PreviousMircros;
unsigned long CurrentMircros;

int CurrentGear = 1;
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

  PreviousMircros = micros();

  Serial.begin(9600);

  // analogtest();
  // digitaltest();
}

void measurespeed()
{
  CurrentMircros = micros();
  OSS[OSS_Measure_Count] = digitalRead(OSS_Pin);
  // bool HasChanged = false; not needed?
  unsigned long timebetween;
  double hz;
  // reset array

  if (OSS_Measure_Count < OSS_Smoothing - 1)
    OSS_Measure_Count++;
  else
  {
    OSS_Measure_Count = 0;
  }

  double osssum = getAverage(OSS, OSS_Smoothing);

  if (osssum > (2.0 / OSS_Smoothing) and OSSHigh == 0)
  {
    OSSHigh = 1;
    digitalWrite(13, HIGH);
    timebetween = CurrentMircros - PreviousMircros;
    hz = (1.00 / timebetween) * 1000000;
    double s = 6.283185307 * (TireSize / 2.00) * (((hz / OSS_Holes) * GearRatio) / 60);
    // print speed
    //  Serial.println("speed: ");
    //  Serial.println(s);

    OSS_Speeds[OSS_Speed_Count] = s;
    //Serial.println(OSS_Speeds[OSS_Speed_Count]);
    // Serial.println(OSS_Speeds[OSS_Speed_Count]);

    if (OSS_Speed_Count < OSS_Smoothing - 1)
      OSS_Speed_Count++;
    else
    {
      OSS_Speed_Count = 0;
    }

    double newspeed = getDoubleAverage(OSS_Speeds, OSS_Smoothing);
    if(int(newspeed) != int(OSS_Avg_Speed)){
      OSS_Speed_Change = true;
      Serial.println("Speed changed");
      Serial.println(OSS_Avg_Speed);
    }else{
      Serial.println("Speed has not changed");
      Serial.println(OSS_Avg_Speed);
      OSS_Speed_Change = false;
    }
    OSS_Avg_Speed = newspeed;
    
  }

  if (osssum < (2.0 / OSS_Smoothing) and OSSHigh == 1)
  {
    OSSHigh = 0;
    digitalWrite(13, LOW);
    PreviousMircros = CurrentMircros;
  }
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

void loop()
{
  measurespeed();
  if (OSSHigh == 0)
  {
    // double s = getDoubleAverage(OSS_Speeds,OSS_Smoothing);

    // Serial.println(OSS_Speeds[0]);
    //  Serial.print(", ");
    //     Serial.print(OSS_Speeds[1]);
    //  Serial.print(", ");
    //     Serial.print(OSS_Speeds[2]);
    //  Serial.print(", ");
    //     Serial.print(OSS_Speeds[3]);
    //  Serial.print(", ");
    //  Serial.print(OSS_Speeds[4]);
    //  Serial.println("a");
    //  }
    // Serial.print(",");
  }
  // Serial.println("desired gear:" + desiredgear());
  //  CurrentMircros = Mircros();
  //  test();
  //  Serial.println(analogRead(EPCPressure_Pin));
  //  Serial.println(digitalRead(OSS_Pin));
}

int desiredgear()
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

  double loadavg = getAverage(Load, Load_Smoothing);
  double speedavg = getDoubleAverage(OSS_Speeds, OSS_Smoothing);

  if (CurrentGear == 1)
  {
    if (loadavg * speedavg > (loadavg * 0.389 + 5.11))
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
    if (loadavg * speedavg > (loadavg * 0.778 + 10.2))
    {
      return 3;
    }
    else if (loadavg * speedavg < (loadavg * 0.333 + 3.67))
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
    if (loadavg * speedavg > (loadavg * 1.17 + 14.3))
    {
      return 4;
    }
    else if (loadavg * speedavg < (loadavg * 0.722 + 8.78))
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
    if (loadavg * speedavg < (loadavg * 1.06 * 13.4))
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

  return avg;
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

  return avg;
}