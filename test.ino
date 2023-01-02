//solenoid/clutch apply chart-----
// PRN1 1/0
// 2 0/0
// 3 0/1
// 4 1/1

//Curves--------------------------
//1st gear UP = 0.389x +5.11
//
//2nd gear DOWN = 0.333x +3.67
//2nd gear UP = 0.778x +10.2
//
//3rd gear DOWN = 0.722x +8.78
//3rd gear UP = 1.17x +14.3
//
//4th gear DOWN = 1.06x +13.4
//
//Line Pressure = 0.389x +56.1

void setup() {
  pinMode(2, OUTPUT);
  pinMode(1, INPUT);
  digitalWrite(2, LOW);
}
int count = 0;
void loop() {
  int val = digitalRead(4);
  if(val){
    count = count + 1;
  }
  if(count ==4){
    digitalWrite(2, HIGH);
  }

    while(val == 1 && digitalRead(1)){
}
    digitalWrite(2, LOW);
    }
