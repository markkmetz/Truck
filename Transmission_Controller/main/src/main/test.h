#ifndef _TEST_H
#define _TEST_H

#include "main.h"



#ifndef TEST
#include <mcp2515.h>
#else
#include "mock2515.h"
#include <cstdint>
#include <string>
#include <iostream>
#include <assert.h>




int main();
void curve_Test();
void Shift_Test();
void MeasureSpeed_Test();
void MeasureISS_Test();
void RegulateEPC_Test();
void TCCLockup_Test();
void SendCanData_Test();
void PrintSerialData_Test();
void splitIntoTwoBytes_Test();
void CheckShift_Test();
void MeasurePressures_Test();
void Shift_Test();
void CalculateGear_Test();
void CalcShiftValue_Test();
void CalcPressureValue_Test();
void getDoubleAverage_Test();
void getDoubleAverageWithoutExtremeValues_Test();
void getAverage_Test();
void ManualMode_Test();

#endif
#endif