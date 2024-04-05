#ifndef MOCK2515_H
#define MOCK2515_H

#ifdef TEST
#include <cstdint>
#include <thread>
#include <iostream>
#include <chrono>


typedef uint8_t byte;
typedef std::string String;



struct can_frame
{
    int can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    int can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    int data[8];
};

enum CAN_CLOCK {
    MCP_20MHZ,
    MCP_16MHZ,
    MCP_8MHZ
};

enum CAN_SPEED {
    CAN_5KBPS,
    CAN_10KBPS,
    CAN_20KBPS,
    CAN_31K25BPS,
    CAN_33KBPS,
    CAN_40KBPS,
    CAN_50KBPS,
    CAN_80KBPS,
    CAN_83K3BPS,
    CAN_95KBPS,
    CAN_100KBPS,
    CAN_125KBPS,
    CAN_200KBPS,
    CAN_250KBPS,
    CAN_500KBPS,
    CAN_1000KBPS
};

class MCP2515
{
public:
    enum ERROR
    {
        ERROR_OK = 0,
        ERROR_FAIL = 1,
        ERROR_ALLTXBUSY = 2,
        ERROR_FAILINIT = 3,
        ERROR_FAILTX = 4,
        ERROR_NOMSG = 5
    };

    static void sendMessage(struct can_frame *can_frame);
    MCP2515(int num);
    static void reset();
    static void setBitrate(int bps, int mhz);
    static void setNormalMode();
    static int readMessage(struct can_frame *frame);
};

class MockSerial
{
public:
    MockSerial();
    void begin(int num);
    void println(String s);
    void println(double d);
    void print(uint32_t u);
    int read();
    void print(String s);
};


static uint32_t pulseIn(int i, byte j){
    return 0;
}

static double constrain(double amt, double low, double high){
    return 0.0;
}

#define PIN_A0   (54)
#define PIN_A1   (55)
#define PIN_A2   (56)
#define PIN_A3   (57)
#define PIN_A4   (58)
#define PIN_A5   (59)
#define PIN_A6   (60)
#define PIN_A7   (61)
#define PIN_A8   (62)
#define PIN_A9   (63)
#define PIN_A10  (64)
#define PIN_A11  (65)
#define PIN_A12  (66)
#define PIN_A13  (67)
#define PIN_A14  (68)
#define PIN_A15  (69)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;
static const uint8_t A8 = PIN_A8;
static const uint8_t A9 = PIN_A9;
static const uint8_t A10 = PIN_A10;
static const uint8_t A11 = PIN_A11;
static const uint8_t A12 = PIN_A12;
static const uint8_t A13 = PIN_A13;
static const uint8_t A14 = PIN_A14;
static const uint8_t A15 = PIN_A15;



/*!
 *  \addtogroup mock
 *  @{
 */

// ----------------- Arduino Digital I/O --------------------------

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino digitalRead().
 @param  pin
 The digital pin to read from.
 @return The mocked digitalRead() value, i.e., zero.
 */
//-----------------------------------------------------------------
static uint16_t digitalRead(uint8_t pin)
{
    return 0;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino digitalWrite() returns without action.
 @param  pin
 Arduino pin number for write.
 @param  value
 Value is either HIGH or LOW.
 */
//-----------------------------------------------------------------
static void digitalWrite(uint8_t pin, uint8_t value){};

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino pinMode() returns without action.
 @param  pin
 Arduino pin number to set the mode.
 @param  mode
 Sets the mode to INPUT, OUTPUT, or INPUT_PULLUP.
 */
//-----------------------------------------------------------------
static void pinMode(uint8_t pin, uint8_t mode){};

//------------------ Arduino Analog I/O ---------------------------

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino analogRead().
 @param  pin
 The analog pin to read from.
 @return The mocked analogRead() value, i.e., zero.
 */
//-----------------------------------------------------------------
static uint16_t analogRead(uint8_t pin)
{
    return 1000;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino analogWrite() returns without action.
 @param  pin
 The analog pin to write to.
 @param  value
 The duty cycle: between 0 (off) and 255 (on).
 */
//-----------------------------------------------------------------
static void analogWrite(uint8_t pin, uint16_t value){};

// --------------------- Arduino Time -----------------------------

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino millis().
 @return Returns 0.
 */
//-----------------------------------------------------------------
static uint32_t millis(void)
{
    return 0L;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino micros().
 @return Returns 0.
 */
//-----------------------------------------------------------------
static uint32_t micros(void)
{
    return 0L;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino delay().
 @param  ms_delay
 The time to pause the code execution.
 */
//-----------------------------------------------------------------
static void delay(uint32_t ms_delay)
{
    ;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked Arduino delayMicroseconds().
 @param  us_delay
 The time to pause the code execution.
 */
//-----------------------------------------------------------------
static void delayMicroseconds(uint32_t us_delay)
{
    ;
};

// --------------------- Arduino Math -----------------------------

//-----------------------------------------------------------------
/*!
 @brief  Re-maps a number from one range to another. That is, a value of
 in_min would get mapped to out_min, a value of in_max to out_max,
 values in-between to values in-between, etc.
 @param  in_value
 The in value to map.
 @param  in_min
 The lower bound of the value’s current range.
 @param  in_max
 The upper bound of the value’s current range.
 @param  out_min
 The lower bound of the value’s target range.
 @param  out_max
 The upper bound of the value’s target range.
 @return The mapped value.
 */
//-----------------------------------------------------------------
static uint32_t map(uint32_t in_value, uint32_t in_min, uint32_t in_max,
                    uint32_t out_min, uint32_t out_max)
{
    return ((in_value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
};

// ------------------ Arduino EEPROM library -----------------------

// Mocked EEPROM library methods
//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM read().
 @param  address
 Read a byte from EEPROM address.
 @return The mocked read() value, i.e., zero.
 */
//-----------------------------------------------------------------
static uint16_t read(uint16_t address)
{
    return 0;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM write() returns without action.
 @param  address
 The EEPROM address to write a byte.
 @param  value
 The value (byte) to write at that address.
 */
//-----------------------------------------------------------------
static void write(uint16_t address, uint16_t value){};

//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM update() returns without action.
 @param  address
 The EEPROM address to write a byte.
 @param  value
 The value to write (byte), if different at that address.
 */
//-----------------------------------------------------------------
static void update(uint16_t address, uint16_t value){};

//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM get().
 @param  address
 Read from EEPROM address.
 @param  data
 Read any data type or object from the EEPROM.
 @return The mocked get() value, i.e., zero.
 */
//-----------------------------------------------------------------
static uint16_t get(uint16_t address, uint16_t data)
{
    return 0;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM put().
 @param  address
 The EEPROM address to write a byte.
 @param  data
 Write data to EEPROM address.
 */
//-----------------------------------------------------------------
static void put(uint16_t address, uint16_t data){};

//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM length().
 @return The mocked length() value, i.e., zero.
 */
//-----------------------------------------------------------------
static uint16_t length(void)
{
    return 0;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM begin().
 @return The mocked begin() value, i.e., hex zero.
 */
//-----------------------------------------------------------------
static uint16_t begin(void)
{
    return 0x00;
};

//-----------------------------------------------------------------
/*!
 @brief  Mocked EEPROM end().
 @return The mocked end() value, i.e., zero length.
 */
//-----------------------------------------------------------------
static uint16_t end(void)
{
    return 0;
};

/*! @} End of Doxygen Groups*/

#ifndef ARDUINO

#define HIGH 0x1 ///< Arduino definition for HIGH
#define LOW 0x0  ///< Arduino definition for LOW

#define INPUT 0x0        ///< Arduino definition for INPUT
#define OUTPUT 0x1       ///< Arduino definition for OUTPUT
#define INPUT_PULLUP 0x2 ///< Arduino definition for INPUT_PULLUP

#define CHANGE 1  ///< Arduino definition for CHANGE
#define FALLING 2 ///< Arduino definition for FALLING
#define RISING 3  ///< Arduino definition for RISING

// Arduino standard typedef's
/** Arduino typedef for word */
typedef uint16_t word;
/** Arduino typedef for boolean */
typedef bool boolean;
/** Arduino typedef for byte */
typedef uint8_t byte;

#endif
#endif
#endif /* MOCK_H_ */
