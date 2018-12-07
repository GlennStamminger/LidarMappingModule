#include "IMapping.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <vector>

#include "Servo.h"
#include "Uart.h"

class MappingLogic : public IMapping
{
private:
  Servo* servo;
  Uart* uart;
  int measuredDistance;
  uint8_t currentStep;
  bool stepMovingUp = true;
public:
  MappingLogic();
  int GetStatus();
  int GetDistanceAtAngle(int angle);
  std::vector<int> GetMap();
  void Update();
};
