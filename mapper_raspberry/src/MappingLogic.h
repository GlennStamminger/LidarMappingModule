#include "IMapping.h"

static void RunLidar(Uart *uart);

class MappingLogic : public IMapping
{
private:
  Servo *servo;
  Uart *uart;
  uint16_t distance;
  uint8_t currentStep;
  bool stepMovingUp = true;
  
public:
  MappingLogic();
  ~MappingLogic();
  std::vector<int> GetMap();
  void Update();
};

