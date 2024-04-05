#include "test.h"
#ifdef TEST

int main()
{
  std::cout << "Starting Unit tests.." << std::endl;

  getAverage_Test();
  getDoubleAverage_Test();
  splitIntoTwoBytes_Test();
  CheckShift_Test();
  curve_Test();
  CalculateGear_Test();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}

void curve_Test()
{
  // Test scenario: all points on the FirstUP are below the same index on the SecondUp
  for (int i = 0; i < 11; ++i)
  {
    assert(bettercurves[FirstUP].shiftPoints[i] < bettercurves[SecondUp].shiftPoints[i]);
  }

  // Test scenario: all points on the SecondUp are below the same index on the ThirdUp
  for (int i = 0; i < 11; ++i)
  {
    assert(bettercurves[SecondUp].shiftPoints[i] < bettercurves[ThirdUp].shiftPoints[i]);
  }

  // Test scenario: all points on the ThirdUp are above the FourthUP
  for (int i = 0; i < 11; ++i)
  {
    assert(bettercurves[ThirdUp].shiftPoints[i] > bettercurves[FourthDown].shiftPoints[i]);
  }

  // Test scenario: all points on the SecondDown are below the same index on the ThirdDown
  for (int i = 0; i < 11; ++i)
  {
    assert(bettercurves[SecondDown].shiftPoints[i] < bettercurves[ThirdDown].shiftPoints[i]);
  }

  // Test scenario: all points on the ThirdDown are below the same index on the FourthDown
  for (int i = 0; i < 11; ++i)
  {
    assert(bettercurves[ThirdDown].shiftPoints[i] < bettercurves[FourthDown].shiftPoints[i]);
  }
};
void Shift_Test(){};
void MeasureSpeed_Test(){};
void MeasureISS_Test(){};
void RegulateEPC_Test(){};
void TCCLockup_Test(){};
void SendCanData_Test(){};
void PrintSerialData_Test(){};
void splitIntoTwoBytes_Test()
{
  byte byte1, byte2;

  // Test with zero
  splitIntoTwoBytes(0x0000, byte1, byte2);
  assert(byte1 == 0x00 && byte2 == 0x00);

  // Test with maximum possible value for a byte
  splitIntoTwoBytes(0x00FF, byte1, byte2);
  assert(byte1 == 0x00 && byte2 == 0xFF);

  // Test with a value that has both bytes non-zero
  splitIntoTwoBytes(0xABCD, byte1, byte2);
  assert(byte1 == 0xAB && byte2 == 0xCD);

  // Test with the maximum int value (assuming 4-byte int)
  splitIntoTwoBytes(0xFFFFFFFF, byte1, byte2);
  assert(byte1 == 0xFF && byte2 == 0xFF);

  // Test with a negative value
  splitIntoTwoBytes(-1, byte1, byte2);
  assert(byte1 == 0xFF && byte2 == 0xFF);
}
void CheckShift_Test(){

};
void MeasurePressures_Test(){};
void CalculateGear_Test()
{

  CurrentGear = 1;
  for (int load = -10; load < 120; load++)
  {
    Load_Avg = load;
    for (int speed = -10; speed < 120; speed++)
    {
      OSS_Avg_Speed = speed;
      
      assert(CalculateGear() > 0);  
      assert(CalculateGear() < 5);

      //we should never be in a gear higher than 1st at 0mph
      if (speed < 1){
        // assert(CalculateGear() == 1);
      }
        
      //we should never be in a gear lower than 3 at 100mph
      if (speed > 101){
       // assert(CalculateGear() > 2);
      }

    }
  }
};
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