const String Version = "10.20.23.1";

#include <SPI.h>
#include <mcp2515.h>
//https://github.com/autowp/arduino-mcp2515


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

//mcp2515 pinout
//cs =  48 digital pin
//si = 51
//so = 50
//sck = 52
//int = n/a


// EPC
// Line Pressure = 0.389x +56.1
// 290hz?
#pragma endregion notes

#pragma region variables

struct can_frame canMsg;
MCP2515 mcp2515(48);

const int tpsindex = 2;  //this is the id of the realtime data broadcasting packet
const int dataindex = 0;
struct BroadcastPacket {
  int tpsvalue;
  //int dataid = 1523;  //this is the id of the realtime data broadcasting packet
  int dataid = -13;
  int other1;
  int other2;
  int other3;  
};


BroadcastPacket bp = {};

enum CurveName{
  FirstUP = 0,
  SecondDown = 1,
  SecondUp = 2,
  ThirdDown = 3,
  ThirdUp = 4,
  FourthDown = 5
};

struct Curve {
  CurveName curvename;
  float y0;
  float y100;
  float slope;
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
Curve defaultcurves[6] = {
  { FirstUP, 5.11, 44.01 },
  { SecondDown, 3.67, 36.67 },
  { SecondUp, 10.2, 88 },
  { ThirdDown, 8.78, 80.98 },
  { ThirdUp, 14.3, 131.3 },
  { FourthDown, 13.4, 119.4 }
};


// INPUTS
const byte ISS_Pin = 8;
const byte OSS_Pin = 9;
const byte LinePressure_Pin = A1;
const byte EPCPressure_Pin = A0;

// OUTPUTS
int TCC_Pin = 3;  // make sure this is an analog pin
int SolA_Pin = 4;
int SolB_Pin = 5;
int EPC_Pin = 2;  // make sure this is an analog pin

// Constants
const int OSS_Holes = 12;
const double GearRatio = 3.55;
const double TireSize = 33;

const int TCC_Max = 0.75 * 255;
const int TCC_Min = 0.3 * 255;
const double TCC_Seconds_Before = .1;

const int ISS_Smoothing = 5;
const int OSS_Smoothing = 5;

const int EPC_Start_Time = 50;
int EPC_Start_PWM = 220;

// Variables
bool Load_Change = false;  // not used except for testing? TODO
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

unsigned long Shift_Previous_Millis;
unsigned long Shift_Current_Millis;

unsigned long TCC_Previous_Millis;
unsigned long TCC_Current_Millis;

// testing variables
bool enableEPC = false;
bool enabletestshifting = false;
bool manualmode = 0;
bool loggingenabled = 1;
int cmd = -1;

bool waitingtcc = false;
bool shifting = false;
int CurrentGear = 1;

unsigned long EPC_Start_Millis;

int EPCPWM = 0;

int CommandedGear = 1;
// int DesiredGear = 0; not needed?
#pragma endregion variables

void setup() {
  pinMode(TCC_Pin, OUTPUT);
  pinMode(SolA_Pin, OUTPUT);
  pinMode(SolB_Pin, OUTPUT);
  pinMode(EPC_Pin, OUTPUT);

  pinMode(ISS_Pin, INPUT);
  pinMode(OSS_Pin, INPUT);
  pinMode(LinePressure_Pin, INPUT);
  pinMode(EPCPressure_Pin, INPUT);

  //Can Bus stuff
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.begin(9600);
  Serial.println(Version);

  OSS_Previous_Mircros = micros();
  
  if (!verifycurves()) {
    Serial.println("Error with shift curves. Halting execution.");
    while (1 == 2) {
      delay(1000);
    }
  }
}

void loop() {
  cmd = Serial.read();
  BroadcastPacket lol = GetCanPacket();
  if(lol.dataid == 1523){
Load_Avg = lol.tpsvalue;
  Serial.println(Load_Avg);
  
  }
  //Serial.print(bp.tpsvalue); //n/a
  //Serial.println("%");


  if (cmd == 109)  // m --toggle mode
    manualmode = !manualmode;

  if (manualmode) {
    switch (cmd) {
      case 49:  // 1 --shift to 1st gear
        {
          CommandedGear = 1;
          Shift();
          break;
        }
      case 50:  // 2 --shift to 2nd gear
        {
          CommandedGear = 2;
          Shift();
          break;
        }
      case 51:  // 3 --shift to 3rd gear
        {
          CommandedGear = 3;
          Shift();
          break;
        }
      case 52:  // 4 --shift to 4th gear
        {
          CommandedGear = 4;
          Shift();
          break;
        }
      case 48:  // 0 --shift to imaginary 0th gear
        {
          CommandedGear = 0;
          Shift();
          break;
        }
      case 53:  // 4 --shift to imaginary 5th gear
        {
          CommandedGear = 5;
          Shift();
          break;
        }
      case 54:  // 6 --shift to imaginary 6th gear
        {
          CommandedGear = 6;
          Shift();
          break;
        }
      case 55:  // 7 --shift to imaginary -1th gear
        {
          CommandedGear = -1;
          Shift();
          break;
        }
      case 101:  // e --toggle epc
        {
          enableEPC = !enableEPC;

          //shutdown epc. should probably be a function
          EPCPWM = 0;
          analogWrite(EPC_Pin, EPCPWM);

          Serial.print("EPC = ");
          Serial.println(enableEPC);
          break;
        }
      case 116:  // t --toggle torque converter TODO
        {
          Serial.println("not implemented");
          break;
        }
      case 108:  // l --increment fake load data
        {
          Load_Avg = Load_Avg + 10;
          Serial.print("Load is set to: ");
          Serial.println(Load_Avg);

          Load_Change = true;
          break;
        }
      case 76:  // L --decrement fake load data
        {
          Load_Avg = Load_Avg - 10;
          Serial.print("Load is set to: ");
          Serial.println(Load_Avg);

          Load_Change = true;
          break;
        }
      case 99:  // c --calc shift
        {
          CheckShift();
          break;
        }
      case 111:  // o --increment OSS data
        {
          OSS_Avg_Speed;

          int newspeed = OSS_Avg_Speed + 10;
          if (newspeed > 130)
            newspeed = -20;
          for (int i = 0; i < OSS_Smoothing; i++) {
            OSS[i] = newspeed;
          }
          OSS_Avg_Speed = getAverage(OSS, OSS_Smoothing);
          Serial.print("Speed is set to: ");
          Serial.println(OSS_Avg_Speed);

          OSS_Speed_Change = true;
          break;
        }
      case 79:  // O --decrement OSS data
        {
          OSS_Avg_Speed;

          int newspeed = OSS_Avg_Speed - 5;
          if (newspeed > 130)
            newspeed = -20;
          for (int i = 0; i < OSS_Smoothing; i++) {
            OSS[i] = newspeed;
          }
          OSS_Avg_Speed = getAverage(OSS, OSS_Smoothing);
          Serial.print("Speed is set to: ");
          Serial.println(OSS_Avg_Speed);

          OSS_Speed_Change = true;
          break;
        }
      case 65:  // A --toggle shifting based on checkshift()
        {
          enabletestshifting = !enabletestshifting;
          Serial.print("debug shifting is currently: ");
          Serial.println(enabletestshifting);
          break;
        }
      case 118:  // v --verify curves
        {
          if (verifycurves()) {
            Serial.println("Shift curves good.");
          } else {
            Serial.println("Error with shift curves");
          }
          break;
        }
      case 43:  // + --shift y int of curves up by 2
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
      case 45:  // -    -shift y int of curves down by 2
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
      default:  // command not found
        {
          if (cmd != -1) {
            Serial.println(cmd);
          }
          break;
        }
    }
    if (cmd != -1) {
      Serial.println("");
    }
    cmd = -1;

    if (enableEPC) {
      RegulateEPC();
    }

    if (enabletestshifting) {
      if (CommandedGear != CurrentGear)
        Shift();
    }

    if (OSS_Speed_Change || Load_Change) {
      OSS_Speed_Change = false;
      Load_Change = false;
      CheckShift();
    }
  } else {
    //MeasureLoad();
    // Serial.println("Manually setting load to 10%!!!!");
    // Load_Avg = 10;

    MeasureSpeed();

    RegulateEPC();

    if (OSS_Speed_Change)
      CheckShift();
    // else
    //   DumpInfo();

    // DetermineTCCLockup(); TODO

    if (CommandedGear != CurrentGear)
      Shift();
  }
}

BroadcastPacket GetCanPacket(){
BroadcastPacket bptemp = {};

  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {

    if(canMsg.can_id == 1523){
    bptemp.dataid = canMsg.can_id;
    bptemp.tpsvalue = canMsg.data[1] | canMsg.data[0] << 8;

    bptemp.tpsvalue = bptemp.tpsvalue/10;
    //Serial.print(bptemp.dataid);
    //Serial.println(bptemp.tpsvalue);
    }
    //TODO filter canid for packettype
    //Serial.print("CanID "); 
    //Serial.print(canMsg.can_id); // print ID

    //Serial.print(", CanDLC ");
    //Serial.print(canMsg.can_dlc); // print DLC
    
    //Serial.print(", CanData: ");
    
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      //Serial.print(canMsg.data[i],HEX);
      //Serial.print(" ");
    }
    //Serial.println("");
  }
  if(bptemp.dataid == 1523){
    return bptemp;
  }

}

void MeasureSpeed() {
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

  if (ossavg > (2.0 / OSS_Smoothing) and OSSHigh == 0) {
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
    else {
      OSS_Speed_Count = 0;
    }

    double newspeed = getDoubleAverage(OSS_Speeds, OSS_Smoothing);
    if (int(newspeed) != int(OSS_Avg_Speed)) {
      OSS_Speed_Change = true;
    } else {
      OSS_Speed_Change = false;
    }
    OSS_Avg_Speed = newspeed;
  }

  if (ossavg < (2.0 / OSS_Smoothing) and OSSHigh == 1) {
    OSSHigh = 0;
    digitalWrite(13, LOW);
    OSS_Previous_Mircros = OSS_Current_Mircros;
  }
}

void RegulateEPC() {
  if (Load_Avg < 0) {
    Load_Avg = 0;
    if (loggingenabled) {
      Serial.println("RegulateEPC(): LOAD too LOW setting to 0 and continuing..");
    }
  }

  unsigned long epctemptime = millis();
  
  if (EPCPWM == 0 && EPC_Start_Millis == 0){
    EPC_Start_Millis = epctemptime;

    if (loggingenabled)
      Serial.println("epc starting up.. ");
  } 
  
  if( epctemptime - EPC_Start_Millis < EPC_Start_Time) {
    //Start up
    
    analogWrite(EPC_Pin, EPC_Start_PWM);

    if (loggingenabled)
      Serial.print("epc startup pwm: ");
      Serial.println(EPC_Start_PWM);
      
  } else {
    EPC_Start_Millis = 0;
    // 0.4x + 56
    EPCPWM = ((0.4 * Load_Avg) + 60) * 2.55;

    if (EPCPWM > 255) {
      EPCPWM = 255;
      if (loggingenabled) {
        Serial.print("epc pwm too HIGH setting to 255: ");
        Serial.println(EPCPWM);
      }
    }
    Serial.println(EPCPWM);
    analogWrite(EPC_Pin, EPCPWM);
  }
}

void DetermineTCCLockup() {
  TCC_Current_Millis = millis();

  if (TCC_Current_Millis - TCC_Previous_Millis > .25)
    waitingtcc = false;

  TCC_Previous_Millis = TCC_Current_Millis;

  // TODO make this a function of load_avg + temp + rpm
  if (CurrentGear == 4 and Load_Avg < 0.75 and !shifting) {
    analogWrite(TCC_Pin, TCC_Max);
    waitingtcc = true;
  } else
    analogWrite(TCC_Pin, 0);
}

void DumpInfo() {
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

void CheckShift() {
  CommandedGear = CalculateGear();
  if (loggingenabled) {
    Serial.print("CheckShift(): current/commanded: ");
    Serial.print(CurrentGear);
    Serial.print(",");
    Serial.println(CommandedGear);
    Serial.print("CheckShift(): speed/load: ");
    Serial.print(OSS_Avg_Speed);
    Serial.print(",");
    Serial.println(Load_Avg);
  }
  if (CurrentGear != CommandedGear) {
    Serial.print("gear: ");
    Serial.print(CommandedGear);
    Serial.print(",speed: ");
    Serial.println(OSS_Avg_Speed);
  }
}

void Shift() {
  // solenoid/clutch apply chart-----
  //  PRN1 1/0
  //  2 0/0
  //  3 0/1
  //  4 1/1

  if (loggingenabled) {
    Serial.print("Shifting from ");
    Serial.print(CurrentGear);
    Serial.print(" to ");
    Serial.println(CommandedGear);
  }

  // give tcc time to lock before shifting again?
  Shift_Current_Millis = millis();
  if (Shift_Current_Millis - Shift_Previous_Millis > .1) {
    shifting = false;
  }

  shifting = true;
  Shift_Previous_Millis = Shift_Current_Millis;

#pragma region redundant value checks
  if (CurrentGear - CommandedGear > 1) {
    CommandedGear = CurrentGear - 1;
    if (loggingenabled) {
      Serial.println("Error: skipping a DOWN shift gear.");
      Serial.print("New desired gear is: ");
      Serial.println(CommandedGear);
    }
  }

  if (CommandedGear - CurrentGear > 1) {
    CommandedGear = CurrentGear + 1;
    if (loggingenabled) {
      Serial.println("Error: skipping an UP shift gear.");
      Serial.print("New desired gear is: ");
      Serial.println(CommandedGear);
    }
  }

  if (CommandedGear == CurrentGear) {
    if (loggingenabled)
      Serial.println("Error: shifting to same gear.");
    return;
  }

  if (CommandedGear > 4 || CommandedGear < 1) {
    if (loggingenabled) {
      Serial.print("Error: shifting to imaginary gear: ");
      Serial.println(CommandedGear);
      Serial.println("Canceling shift..");
    }
    CommandedGear = CurrentGear;
    return;
  }
#pragma endregion

  if (CommandedGear == 1) {
    digitalWrite(SolA_Pin, HIGH);
    digitalWrite(SolB_Pin, LOW);
    CurrentGear = 1;
  } else if (CommandedGear == 2) {
    digitalWrite(SolA_Pin, LOW);
    digitalWrite(SolB_Pin, LOW);
    CurrentGear = 2;
  } else if (CommandedGear == 3) {
    digitalWrite(SolA_Pin, LOW);
    digitalWrite(SolB_Pin, HIGH);
    CurrentGear = 3;
  } else if (CommandedGear == 4) {
    digitalWrite(SolA_Pin, HIGH);
    digitalWrite(SolB_Pin, HIGH);
    CurrentGear = 4;
  }
}

int CalculateGear() {
  if (OSS_Avg_Speed < 0) {
    OSS_Avg_Speed = 0;

    if (loggingenabled)
      Serial.println("Speed < 0; setting to 0.");
  }

  if (OSS_Avg_Speed > 120) {
    OSS_Avg_Speed = 120;

    if (loggingenabled)
      Serial.println("Speed > 120; setting to 120.");
  }

  if (Load_Avg < 0) {
    Load_Avg = 0;

    if (loggingenabled)
      Serial.println("Load < 0; setting to 0.");
  }

  if (Load_Avg > 100) {
    Load_Avg = 100;

    if (loggingenabled)
      Serial.println("Speed > 100; setting to 100.");
  }

  if (CurrentGear == 1) {

    if (OSS_Avg_Speed > (CalcCurveValue(FirstUP,Load_Avg))) {
      return 2;
    } else {
      return 1;
    }
  } else if (CurrentGear == 2) {
    if (OSS_Avg_Speed > (CalcCurveValue(SecondUp,Load_Avg))) {
      return 3;
    } else if (OSS_Avg_Speed < (CalcCurveValue(SecondDown,Load_Avg))) {
      return 1;
    } else {
      return 2;
    }
  } else if (CurrentGear == 3) {
    if (OSS_Avg_Speed > (CalcCurveValue(ThirdUp,Load_Avg))) {
      return 4;
    } else if (OSS_Avg_Speed < (CalcCurveValue(ThirdDown,Load_Avg))) {
      return 2;
    } else {
      return 3;
    }
  } else if (CurrentGear == 4) {
    if (OSS_Avg_Speed < (CalcCurveValue(FourthDown,Load_Avg))) {
      return 3;
    } else {
      return 4;
    }
  } else {
    return 0;
  }
}

//Calulate the y value (speed) from the shift curves.
double CalcCurveValue(CurveName cname,double load){
  double m = (defaultcurves[cname].y100 - defaultcurves[cname].y0)/100;
  return (((m*load) + defaultcurves[cname].y0));
}

double getDoubleAverage(double arr[], int size) {
  int i = 0;
  double sum = 0;
  double avg;

  for (i = 0; i < size; ++i) {
    sum += arr[i];
  }
  avg = sum / size;

  if (avg > 140) {
    Serial.println("error at getdoubleaverage()");
    DumpInfo();
    return OSS_Avg_Speed;
  } else {
    return avg;
  }
}

double getAverage(int arr[], int size) {
  int i, sum = 0;
  double avg;

  for (i = 0; i < size; ++i) {
    sum += arr[i];
  }
  avg = double(sum) / size;
  if (avg > 140) {
    Serial.println("error at getAverage()");
    DumpInfo();
  }
  return avg;
}

bool verifycurves() {
  // the previous upshift curve will always be above the next gears down shift
  // for example: 1 up has a higher y val than 2 down

  float prevslope = 0;
  for (Curve c : defaultcurves) {
    c.slope = (c.y100 - c.y0) / 100;

    if (loggingenabled) {
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
