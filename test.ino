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


//OUTPUTS
int TCC_Pin = 10;
int SolA_Pin = 11;
int SolB_Pin = 12;
int EPC_Pin = 13;

//Variables
int Load = digitalRead(Load_Pin);
int ISS = digitalRead(ISS_Pin);
int OSS = digitalRead(OSS_Pin);


void setup() {
  pinMode(TCC_Pin, OUTPUT);
  pinMode(SolA_Pin, OUTPUT);
  pinMode(SolB_Pin, OUTPUT);
  pinMode(EPC_Pin, OUTPUT);

  pinMode(Load_Pin, INPUT);
  pinMode(ISSP_in, INPUT);
  pinMode(OSS_Pin, INPUT);



}


void loop() {
  
}
