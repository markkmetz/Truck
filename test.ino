
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
