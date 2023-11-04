#include <ACAN_ESP32.h>
// #include <ACAN_ESP32_AcceptanceFilters.h>
// #include <ACAN_ESP32_Buffer16.h>
// //#include <ACAN_ESP32_CANRegisters.h>
// #include <ACAN_ESP32_Settings.h>
//#include <CANMessage.h>

//https://github.com/pierremolinaro/acan-esp32/tree/main
// CAN transceiver 	ESP32
//             3V3 	3V3
//             GND 	GND
//             CTX 	GPIO_5
//             CRX 	GPIO_4
//CTX and CRX pins can be changed by using CAN.setPins(rx, tx).


//#include <ACAN_ESP32.h>
#include <core_version.h>
const String version = "10.28.23.1";
const int debouncetime = 1000;
long timenow;

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
  bool Accel;
  bool Res;
  long lastsent = 0;

  bool pressed() {
    timenow = millis();
    if (!this->Off || !this->On || !this->Coast || !this->Accel || !this->Res) {
      if (timenow - this->lastsent > debouncetime) {
        this->lastsent = timenow;
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  }

  void update() {
    this->Off = digitalRead(OFFPIN);
    this->On = digitalRead(ONPIN);
    this->Coast = digitalRead(COASTPIN);
    this->Accel = digitalRead(ACCELPIN);
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
  Serial.println(version);
  ACAN_ESP32_Settings settings(500 * 1000);  // 500 kbit/s
  settings.mRequestedCANMode = ACAN_ESP32_Settings::NormalMode;
  settings.mRxPin = GPIO_NUM_5;
  settings.mTxPin = GPIO_NUM_4;
  const uint32_t errorCode = ACAN_ESP32::can.begin(settings);
  if (0 == errorCode) {
    Serial.println("Can ok");
  } else {
    Serial.print("Error Can: 0x");
    Serial.println(errorCode, HEX);
  }
  timenow = millis();
}

void loop() {

  bp.update();
  writeled(200, 200, 200);
  if (bp.pressed()) {


    CANMessage frame;
    frame.id = 1601;
    frame.data[0] = !bp.Off;
    frame.data[1] = !bp.On;
    frame.data[2] = !bp.Coast;
    frame.data[3] = !bp.Accel;
    frame.data[4] = !bp.Res;
    frame.len = 5;

    const bool ok = ACAN_ESP32::can.tryToSend(frame);
    if (ok) {
      Serial.println("SEnt?");
    }

  } else {
    writeled(0, 0, 200);
  }

  delay(50);  //needed???
}
