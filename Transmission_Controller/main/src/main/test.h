#ifndef _TEST_H
#define _TEST_H
#include "main.h"

void arduinosetup_Test();
void arduinoloop_Test();

void Shift_Test();
void MeasureSpeed_Test();
void MeasureISS_Test();
void RegulateEPC_Test();
void TCCLockup_Test();
void SendCanData_Test();
void PrintSerialData_Test();
void splitIntoTwoBytes_Test(int value, byte &byte1, byte &byte2);
void CheckShift_Test();
void MeasurePressures_Test();
void Shift_Test();
void CalculateGear_Test();
void CalcShiftValue_Test(CurveName cname, double load);
void CalcPressureValue_Test(Curve curve, double load);
void getDoubleAverage_Test(double arr[], int size);
void getDoubleAverageWithoutExtremeValues_Test(int arr[], int size);
void getAverage_Test(int arr[], int size);
void ManualMode_Test();

#endif