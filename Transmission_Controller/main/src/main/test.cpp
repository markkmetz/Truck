#include "test.h"

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

int main()
{

  // getAverage_Test();
  // std::cout << "Hello, World!" << std::endl;
  // return 0;
}

void Shift_Test(){

};
void MeasureSpeed_Test(){};
void MeasureISS_Test(){};
void RegulateEPC_Test(){};
void TCCLockup_Test(){};
void SendCanData_Test(){};
void PrintSerialData_Test(){};
void splitIntoTwoBytes_Test(int value, byte &byte1, byte &byte2);
void CheckShift_Test(){};
void MeasurePressures_Test(){};
void CalculateGear_Test(){};
void CalcShiftValue_Test(CurveName cname, double load);
void CalcPressureValue_Test(Curve curve, double load);
void getDoubleAverage_Test();
void getDoubleAverageWithoutExtremeValues_Test();
void getAverage_Test()
{
  int arr[1] = {0};
  double idk = getAverage(arr, 1);
};
void ManualMode_Test(){};