#include "test.h"
#ifdef TEST


int main()
{
  std::cout << "Starting Unit tests.." << std::endl;

  getAverage_Test();
  getDoubleAverage_Test();

  std::cout << "All tests passed!" << std::endl;
  return 0;
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
void getDoubleAverage_Test()
{
  double arr1[1] = {(double)0.0};
  assert(getDoubleAverage(arr1, 1) == 0.0);

  arr1[0] = 1.0;
  assert(getDoubleAverage(arr1, 1) == 1.0);

  arr1[0] = -1.0;
  assert(getDoubleAverage(arr1, 1) == -1.0);

  double arr2_1[2] = {1.0, 2.0};
  assert(getDoubleAverage(arr2_1, 2) == 1.5);

  double arr2_2[2] = {-1.0, 1.0};
  assert(getDoubleAverage(arr2_2, 2) == 0);

  double arr2_3[2] = {.66666, 1};
  assert(getDoubleAverage(arr2_3, 2) == 0.83333);
}
void getDoubleAverageWithoutExtremeValues_Test();
void getAverage_Test()
{
  int arr1[1] = {0};
  assert(getAverage(arr1, 1) == 0);

  int arr2[1] = {1};
  assert(getAverage(arr2, 1) == 1);

  int arr3[1] = {-1};
  assert(getAverage(arr3, 1) == -1);

  int arr4[2] = {1, 2};
  assert(getAverage(arr4, 2) == 1.5);

  int arr5[2] = {-1, 1};
  assert(getAverage(arr5, 2) == 0);
};
void ManualMode_Test(){};

#endif