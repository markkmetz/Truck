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


class PID
{
private:
  double Kp;
  double Ki;
  double Kd;

  double pre_error;
  double integral;

public:
  // Constructor
  PID(double P, double I, double D)
      : Kp(P), Ki(I), Kd(D), pre_error(0), integral(0) {}

  int calculate(double setpoint, double pv);
  void clear();
  double lastOutput;
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


struct Curve
{
  CurveName curvename;
  int shiftPoints[11];
  int pressurePoints[11];
  int PressureInGearSetpoint;
  int shiftLengthScaler; // Not used yet
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
extern int enginetemp;

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
extern PID inGearPID;

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
void PrintPIDData();
void ReceiveCanData();
int CalculateGear();
double CalcShiftValue(int cname, double load);
double CalcPressureValue(Curve curve, double load);
double getDoubleAverage(double arr[], int size);
int getDoubleAverageWithoutExtremeValues(int arr[], int size);
double getAverage(int arr[], int size);
void ManualMode();

#endif
