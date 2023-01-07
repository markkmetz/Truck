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
const byte Load_Pin = A4;
const byte ISS_Pin = 3;
const byte OSS_Pin = 2;
const byte LinePressure_Pin = A1;
const byte EPCPressure_Pin = A0;

//OUTPUTS
int TCC_Pin = 9; //make sure this is an analog pin
int SolA_Pin = 10; 
int SolB_Pin = 11;
int EPC_Pin = 6; //make sure this is an analog pin

//Constants
const int TCC_Max = 0.75 * 255;
const int TCC_Min = 0.3 * 255;
const int EPC_Max = 0.75 * 255;
const int EPC_Min = 0.3 * 255;
const int Load_Smoothing = 1;
const int ISS_Smoothing = 5;
const int OSS_Smoothing = 5;

//Variables
int speeds = 0;

int Load [Load_Smoothing];
int LoadHigh = 0;

int ISS [ISS_Smoothing];
int ISSHigh = 0;

int OSS [OSS_Smoothing];
int OSSHigh = 0;

unsigned long previousMillis;
unsigned long currentMillis;
int count = 0;

int CurrentGear = 0;
int DesiredGear = 0;

void setup() {
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

  pinMode(13,OUTPUT);

  //RE-ENABLE THIS WHEN YOU ARE READY TO DRIVE!!!!-----------
  //prepare outputs for vehicle startup
  //analogWrite(EPC_Pin, EPC_Max);
  //analogWrite(TCC_Pin, TCC_Max);
  //digitalWrite(SolA_Pin, HIGH);
  //digitalWrite(SolA_Pin, LOW);
  #pragma endregion PinStates
  
  previousMillis = millis();

  Serial.begin(9600);

  //analogtest();
  //digitaltest();
}

void measurespeed(){
  currentMillis = millis();
  OSS[count] = digitalRead(OSS_Pin);
  bool haschanged = false;
  unsigned long timebetween;
  double hz;
  //reset array
  if(count < OSS_Smoothing)
    count++;
  else{
    count = 0;
  }

  int osssum = 0;
  for(int i=0;i<OSS_Smoothing;i++){
    osssum += OSS[i];
  }
  //Serial.println(count);
  if (osssum > OSS_Smoothing-2 and OSSHigh == 0){
    OSSHigh = 1;
    digitalWrite(13,HIGH);
    timebetween = currentMillis - previousMillis;
    hz = (1.00/timebetween)*1000;
    Serial.println(hz);

  }

  if (osssum < OSS_Smoothing -2 and OSSHigh == 1){
    OSSHigh = 0;
    digitalWrite(13,LOW);
    previousMillis = currentMillis;
  }



}

void digitaltest(){

  digitalWrite(EPC_Pin,HIGH);
  delay(1000);
  digitalWrite(EPC_Pin,LOW);

  delay(1000);
  digitalWrite(SolA_Pin,HIGH);
  delay(1000);
  digitalWrite(SolA_Pin,LOW);

  delay(1000);
  digitalWrite(SolB_Pin,HIGH);
  delay(1000);
  digitalWrite(SolB_Pin,LOW);

  delay(1000);
  digitalWrite(TCC_Pin,HIGH);
  delay(1000);
  digitalWrite(TCC_Pin,LOW);
}

void analogtest(){

  delay(1000);
  analogWrite(TCC_Pin,50);
  delay(1000);
  analogWrite(TCC_Pin,100);
  delay(1000);
  analogWrite(TCC_Pin,150);
  delay(1000);
  analogWrite(TCC_Pin,200);
  delay(1000);
  analogWrite(TCC_Pin,250);
  delay(1000);
  analogWrite(TCC_Pin,0);

  delay(1000);
  analogWrite(EPC_Pin,50);
  delay(1000);
  analogWrite(EPC_Pin,100);
  delay(1000);
  analogWrite(EPC_Pin,150);
  delay(1000);
  analogWrite(EPC_Pin,200);
  delay(1000);
  analogWrite(EPC_Pin,250);
  delay(1000);
  analogWrite(EPC_Pin,0);

  delay(1000);
  analogWrite(SolA_Pin,50);
  delay(1000);
  analogWrite(SolA_Pin,100);
  delay(1000);
  analogWrite(SolA_Pin,150);
  delay(1000);
  analogWrite(SolA_Pin,200);
  delay(1000);
  analogWrite(SolA_Pin,250);
  delay(1000);
  analogWrite(SolA_Pin,0);

  delay(1000);
  analogWrite(SolB_Pin,50);
  delay(1000);
  analogWrite(SolB_Pin,100);
  delay(1000);
  analogWrite(SolB_Pin,150);
  delay(1000);
  analogWrite(SolB_Pin,200);
  delay(1000);
  analogWrite(SolB_Pin,250);
  delay(1000);
  analogWrite(SolB_Pin,0);
}

void osstest(){
  
}

void loop() {
  measurespeed();
  //currentMillis = millis();
  //test();
  //Serial.println(analogRead(EPCPressure_Pin));
  //Serial.println(digitalRead(OSS_Pin));
}
