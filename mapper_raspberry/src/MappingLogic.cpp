#include "MappingLogic.h"

//Constructor
MappingLogic::MappingLogic()
    : distance(0)
{
  if (wiringPiSetup () == -1)
  {
    printf("failed to setup");
    exit (1);
  }
  this->servo = new Servo(SERVO_PIN, SERVO_MIN_DEGREE, SERVO_MAX_DEGREE, SERVO_HALF_DEGREE);
  this->uart = new Uart();

  ThreadHandler<Uart *> thread(RunLidar, this->uart);
  Update();
}

MappingLogic::~MappingLogic()
{
  std::cout<<"ending mapping"<<std::endl;
  delete this->uart;
}
 
void MappingLogic::Update()
{
  //has to become delta time
  if (1)
  {
    if (this->stepMovingUp)
    {
      //Move up.
      this->currentStep++;

      //If out of bounds flip direction.
      if (this->currentStep >= 179)
      {
        this->stepMovingUp = false;
      }
    }
    else
    {
      //Move down.
      this->currentStep--;

      //If out of bounds flip direction.
      if (this->currentStep <= 0)
      {
        this->stepMovingUp = true;
      }
    }

    this->distance = this->uart->ReturnDistance();
    this->servo->SetAngle(this->currentStep);
    usleep(3600);
  }
}

uint16_t* MappingLogic::GetMap()
{
  return this->distanceMap;
}

static void RunLidar(Uart *uart)
{
  while (1)
  {
    uart->TfMiniDistance();
  }
}

