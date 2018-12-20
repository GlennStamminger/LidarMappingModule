#ifndef MAPPING_LOGIC_H
#define MAPPING_LOGIC_H
#include "IMapping.h"

//Definitions
#define SERVO_PIN (1)
#define SERVO_MIN_DEGREE (0)
#define SERVO_HALF_DEGREE (90)
#define SERVO_MAX_DEGREE (180)
#define MAP_LINES (5)

class MappingLogic : public IMapping
{
private:
  Servo *servo;
  Uart *uart;
  uint8_t currentStep;
  bool stepMovingUp = true;
  uint16_t distanceMap[MAP_LINES];
  ThreadHandler<Uart*>* uartThread;
  void InitMappingLogic();
  
public:
  MappingLogic();
  ~MappingLogic();
  uint16_t* GetMap();
  void Update();
  void SetMap();
};

#endif