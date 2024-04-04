#ifndef _TEST_H
#define _TEST_H


#include "main.h"


int main();

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
void getDoubleAverage_Test();
void getDoubleAverageWithoutExtremeValues_Test();
void getAverage_Test();
void ManualMode_Test();

#endif