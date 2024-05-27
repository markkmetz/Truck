#ifndef _MAIN_H
#define _MAIN_H

#include "epc.h"

#ifndef TEST
#include <mcp2515.h>
#else
#include "mock2515.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <assert.h>
#include <algorithm>
#endif

enum CurveName
{
  FirstUP = 0,
  SecondDown = 1,
  SecondUp = 2,
  ThirdDown = 3,
  ThirdUp = 4,
  FourthDown = 5
};

struct Curve
{
  CurveName curvename;
  int shiftPoints[11];
  int pressurePoints[11];
  int PressureInGearSetpoint;
  int shiftLengthScaler; // Not used yet
};

class Timer
{
private:
  unsigned long currentTime;
  int timerLength;
  void (*callback)();

public:
  Timer(void (*callback)() = NULL, int length = 0)
  {
    this->callback = callback;
    this->timerLength = length;
  }

  Timer(int length = 0)
  {
    this->timerLength = length;
  }

  unsigned long timerLastStart;
  unsigned long timerLastStop;
  bool isRunning;

  void start(int length)
  {
    currentTime = millis();
    timerLastStart = currentTime;
    timerLastStop = 0;
    timerLength = length;
    isRunning = true;
  }

  void stop()
  {
    currentTime = millis();
    timerLastStop = currentTime;
  }

  /// @return start - current
  unsigned long ElapsedTime()
  {
    return currentTime - timerLastStart;
  }

  bool timerExpired()
  {
    currentTime = millis();
    if (currentTime > (timerLastStart + timerLength))
      return true;
    else
      return false;
  }

  void Run()
  {
    if (!this->isRunning)
    {
      return;
    }

    // increment the timers
    currentTime = millis();
    if (this->timerExpired())
    {
      this->isRunning = false;
      if (this->callback != NULL)
      {
        this->callback();
      }
    }
  }

  void Restart()
  {
    this->stop();
    this->start(this->timerLength);
  }
};

class ShiftingTimer : public Timer
{
  using Timer::Timer;

public:
  Curve ShiftCurve;

  void start(int length, Curve curve)
  {
    ShiftCurve = curve;
    Timer::start(length);
  }
};

class PID
{
private:
  double Kp;
  double Ki;
  double Kd;

  double pre_error;
  double integral;
  double lastOutput;

public:
  // Constructor
  PID(double P, double I, double D)
      : Kp(P), Ki(I), Kd(D), pre_error(0), integral(0) {}

  int calculate(double setpoint, double pv)
  {
    // Calculate error
    double error = setpoint - pv;

    // Proportional term
    double Pout = Kp * error;

    // clamping the Integral term

    integral += error;

    integral = constrain(integral, -1000, 1000);

    double Iout = Ki * integral;

    // Derivative term
    double derivative = (error - pre_error);
    double Dout = Kd * derivative;

    // Calculate total output
    int output = (int)Pout + Iout + Dout;

    // Save error to next loop
    pre_error = error;

    // clamp the output

    lastOutput = output;
    output = constrain(output, 0, 255);

    return output;
  }

  void clear()
  {
    integral = 0;
    pre_error = 0;
    lastOutput = 0;
  }
};

class TCCTimer : public Timer
{
  using Timer::Timer;

public:
  int TCCPWM = 0;

private:
  int msStep = 100;

  void Run()
  {

    Timer::Run();
  }
};

extern Curve bettercurves[6];

extern double OSS_Avg_Speed;
extern double ISS_Avg_Speed;
extern int OSS_Speed_Count;
extern int ISS_Speed_Count;
extern int OSS_Measure_Count;
extern int ISS_Measure_Count;
extern int OSSHigh;
extern int ISSHigh;

extern double Load_Avg;
extern int FuelLevel;
extern int OilPressure;
extern int EPCPressure;
extern int EPCPWM;
extern int EPCSetpoint;
extern int rpmValue;

extern bool tccTimer;
extern bool shifting;
extern int CurrentGear;

extern const byte ISS_Pin;
extern const byte OSS_Pin;
extern const byte Fuel_Level_Pin;
extern const byte OIL_Pressure_PIN;
extern const byte EPC_PRESSURE_PIN;

extern ShiftingTimer shiftingTimer;
extern Timer postShiftTimer;
extern PID shiftingPID;

void arduinosetup();
void arduinoloop();

void Shift();
void MeasureSpeed();
void MeasureISS();
void RegulateEPC();
void TCCLockup();
void SendCanData();
void PrintSerialData();
void splitIntoTwoBytes(int value, byte &byte1, byte &byte2);
void CheckShift();
void MeasurePressures();
void Shift();
int CalculateGear();
double CalcShiftValue(int cname, double load);
double CalcPressureValue(Curve curve, double load);
double getDoubleAverage(double arr[], int size);
int getDoubleAverageWithoutExtremeValues(int arr[], int size);
double getAverage(int arr[], int size);
void ManualMode();

#endif
