#ifndef _MAIN_H
#define _MAIN_H


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
extern int rpmValue;

extern bool tccTimer;
extern bool shifting;
extern int CurrentGear;

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
double CalcShiftValue(CurveName cname, double load);
double CalcPressureValue(Curve curve, double load);
double getDoubleAverage(double arr[], int size);
double getDoubleAverageWithoutExtremeValues(int arr[], int size);
double getAverage(int arr[], int size);
void ManualMode();


#endif

