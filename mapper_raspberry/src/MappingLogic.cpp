#include "MappingLogic.h"

//Definitions
#define SERVO_PIN 15
#define SERVO_MAX_DEGREE 180

//Constructor
MappingLogic::MappingLogic()
    : distance(0)
{
  this->servo = new Servo(SERVO_PIN, 0, 180, 90);
  this->uart = new Uart();

  ThreadHandler<Uart *> thread(RunLidar, this->uart);
  Update();
}

MappingLogic::~MappingLogic()
{
  std::cout<<"ending mapping"<<std::endl;
  delete this->uart;
}

//Variables
std::vector<int> distanceMap(SERVO_MAX_DEGREE);

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

    //this->distance = this->uart->ReturnDistance();
    this->servo->SetAngle(this->currentStep);
    usleep(3600);
  }
}

std::vector<int> MappingLogic::GetMap()
{
  return distanceMap;
}

static void RunLidar(Uart *uart)
{
  while (1)
  {
    uart->TfMiniDistance();
  }
}

