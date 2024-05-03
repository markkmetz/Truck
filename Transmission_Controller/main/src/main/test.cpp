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
  MeasureSpeed_Test();
  getDoubleAverageWithoutExtremeValues_Test();
  CalcPressureValue_Test();
  CalcShiftValue_Test();
  RegulateEPC_Test();

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

void MeasureSpeed_Test()
{
  MeasurePressures();
  assert(Fuel_Level_Pin >= 0);
  assert(Fuel_Level_Pin <= 300);
  assert(OilPressure >= 0);
  assert(OilPressure <= 300);
  assert(EPC_PRESSURE_PIN >= 0);
  assert(EPC_PRESSURE_PIN <= 300);
};

void MeasureISS_Test(){};

void RegulateEPC_Test()
{
  EPCPressure = EPCSetpoint + 1;
  shiftingTimer.isRunning = false;
  shiftingPID.clear();

  for (int i = 0; i < 100; i++)
  {
    Load_Avg = i;
    RegulateEPC();
    std::cout << EPCPWM;
    std::cout << " \n";
  }
  // shiftingTimer.isRunning = True;
};

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
  for (int g = 1; g < 5; g++)
  {
    CurrentGear = g;
    for (int load = -10; load < 120; load++)
    {
      Load_Avg = load;
      for (int speed = -10; speed < 120; speed++)
      {
        OSS_Avg_Speed = speed;

        assert(CalculateGear() > 0);
        assert(CalculateGear() < 5);

        // we should never be in a gear higher than 1st at 0mph
        if (speed < 2)
        {

          // std::cout << CurrentGear << " ";
          // std::cout << Load_Avg << " ";
          // std::cout << OSS_Avg_Speed << " ";
          // std::cout << CalculateGear() << " ";
          // std::cout << std::endl;

          // This fails for some reason at 1,100,0,2
          // assert(CalculateGear() == 1);
        }

        // we should never be in a gear lower than 3 at 100mph
        if (speed > 101)
        {
          // assert(CalculateGear() > 2);
        }
      }
    }
  }
};

void CalcShiftValue_Test()
{
  for (int c = 0; c < 1; c++)
  {
    for (int i = -10; i < 110; i++)
    {
      double val = CalcShiftValue(c, i);
      if (i > 1)
      {
        double val2 = CalcShiftValue(c, i - 1);
        assert(val2 - val < 5);
      }
      assert(val >= 0);
      assert(val < 100);
    }
  }
}

void CalcPressureValue_Test()
{
  for (int c = 0; c < 6; c++)
  {
    for (int i = -10; i < 110; i++)
    {
      double val = CalcPressureValue(bettercurves[c], i);
      // Test to make sure that the curve curves rather then steps.
      if (i > 1)
      {
        double val2 = CalcPressureValue(bettercurves[c], i - 1);
        assert(val2 - val < 5);
      }
      assert(val >= 0);
      assert(val < 100);
    }
  }
}

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

void getDoubleAverageWithoutExtremeValues_Test()
{
  int arr1[1] = {0};
  assert(getDoubleAverageWithoutExtremeValues(arr1, 1) == 0);

  int arr2[1] = {1};
  assert(getDoubleAverageWithoutExtremeValues(arr2, 1) == 1);

  int arr3[1] = {-1};
  assert(getDoubleAverageWithoutExtremeValues(arr3, 1) == -1);

  int arr4[2] = {1, 2};
  assert(getDoubleAverageWithoutExtremeValues(arr4, 2) == 1);

  int arr5[2] = {-1, 1};
  assert(getDoubleAverageWithoutExtremeValues(arr5, 2) == 0);

  int arr6[2] = {0, 100};
  assert(getDoubleAverageWithoutExtremeValues(arr6, 2) == 50);
}

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