#ifndef _MAIN_H
#define _MAIN_H



#ifdef ARDUINO
#include <mcp2515.h>
#else
#include "mock2515.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <assert.h>
typedef uint8_t byte;
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