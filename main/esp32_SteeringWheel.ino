#include <CAN.h>


// CAN transceiver 	ESP32
//             3V3 	3V3
//             GND 	GND
//             CTX 	GPIO_5
//             CRX 	GPIO_4
//CTX and CRX pins can be changed by using CAN.setPins(rx, tx).

//Don't forget about the potentiometer pin!



#define LED_PIN_R 32
#define LED_PIN_G 33
#define LED_PIN_B 25

#define OFFPIN 26    //Off
#define ONPIN 27     //On
#define COASTPIN 14  //Coast
#define ACCELPIN 12  //set accell
#define RESPIN 13    //Res

struct buttonpresses {
  bool Off;
  bool On;
  bool Coast;
  bool AccelPin;
  bool Res;



  bool pressed() {
    if (!this->Off || !this->On || !this->Coast || !this->AccelPin || !this->Res) {
      return true;
    } else {
      return false;
    }
  }

  void update() {
    this->Off = digitalRead(OFFPIN);
    this->On = digitalRead(ONPIN);
    this->Coast = digitalRead(COASTPIN);
    this->AccelPin = digitalRead(ACCELPIN);
    this->Res = digitalRead(RESPIN);
  }
};

void writeled(int r = 0, int g = 0, int b = 0) {
  analogWrite(LED_PIN_R, r);
  analogWrite(LED_PIN_G, g);
  analogWrite(LED_PIN_B, b);
}

buttonpresses bp = {};

void setup() {
  pinMode(LED_PIN_R, OUTPUT);
  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);

  pinMode(OFFPIN, INPUT_PULLUP);
  pinMode(ONPIN, INPUT_PULLUP);
  pinMode(COASTPIN, INPUT_PULLUP);
  pinMode(ACCELPIN, INPUT_PULLUP);
  pinMode(RESPIN, INPUT_PULLUP);

  Serial.begin(9600);

  while (!Serial)
    ;

  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }
}

void loop() {

  bp.update();
  writeled(200, 200, 200);
  if (bp.pressed()) {
    CAN.beginPacket(0x12);
    CAN.write(bp.Off);
    CAN.write(bp.On);
    CAN.write(bp.Coast);
    CAN.write(bp.AccelPin);
    CAN.write(bp.Res);
    CAN.endPacket();

    Serial.println("sent");


  } else {
    writeled(0, 0, 200);
  }

  delay(50);  //needed???
}
