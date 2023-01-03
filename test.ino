//solenoid/clutch apply chart-----
// PRN1 1/0
// 2 0/0
// 3 0/1
// 4 1/1

//Shift Curves--------------------------
//1st gear UP = 0.389x +5.11
//
//2nd gear DOWN = 0.333x +3.67
//2nd gear UP = 0.778x +10.2
//
//3rd gear DOWN = 0.722x +8.78
//3rd gear UP = 1.17x +14.3
//
//4th gear DOWN = 1.06x +13.4

//TODO
//tcc unlock = 20%
//tcc lockup time 3 seconds 30%-70%
//tcc unlock on throttle off?
//unlock tcc as you shift?

//EPC
//Line Pressure = 0.389x +56.1
//290hz?

//INPUTS
int Load_Pin = 15;
int ISS_Pin = 16;
int OSS_Pin = 17;
int LinePressure_Pin = 18;
int EPCPressure_Pin = 18;

//OUTPUTS
int TCC_Pin = 10; //make sure this is an analog pin
int SolA_Pin = 11; 
int SolB_Pin = 12;
int EPC_Pin = 13; //make sure this is an analog pin

//Constants
const int TCC_Max = 0.75 * 255;
const int TCC_Min = 0.3 * 255;
const int EPC_Max = 0.75 * 255;
const int EPC_Min = 0.3 * 255;
const int Load_Smoothing = 1;
const int ISS_Smoothing = 1;
const int OSS_Smoothing = 1;

//Variables
int Load [Load_Smoothing];
int LoadHigh = 0;
int ISS [ISS_Smoothing];
int ISSHigh = 0;
int OSS [OSS_Smoothing];
int OSSHigh = 0;

unsigned long currentMillis;
int count = 0;

int CurrentGear = 0;
int DesiredGear = 0;

void setup() {
  pinMode(TCC_Pin, OUTPUT);
  pinMode(SolA_Pin, OUTPUT);
  pinMode(SolB_Pin, OUTPUT);
  pinMode(EPC_Pin, OUTPUT);

  pinMode(Load_Pin, INPUT);
  pinMode(ISS_Pin, INPUT);
  pinMode(OSS_Pin, INPUT);
  pinMode(LinePressure_Pin, INPUT);
  pinMode(EPCPressure_Pin, INPUT);

  //prepare outputs for vehicle startup
  analogWrite(EPC_Pin, EPC_Max);
  analogWrite(TCC_Pin, TCC_Max);
  digitalWrite(SolA_Pin, HIGH);
  digitalWrite(SolA_Pin, LOW);

}

void measurespeed(){
  //ignoring ISS

  ISS[count] = digitalRead(ISS_Pin);
  

  //reset array
  if(count < ISS_Smoothing)
    count++;
  else{
    count = 0;
  }
}



void loop() {
  measurespeed();
  currentMillis = millis();
  
}
