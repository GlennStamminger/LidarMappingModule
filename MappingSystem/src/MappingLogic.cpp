#include "MappingLogic.h"

static void RunLidar(Uart *uart)
{
  while (1)
  { 
    uart->TfMiniDistance();
  }
}

//Constructor
MappingLogic::MappingLogic()
{
  this->InitMappingLogic();
}

MappingLogic::~MappingLogic()
{
  delete this->uartThread;
  delete this->uart;
}
 
void MappingLogic::Update()
{
    if (this->stepMovingUp)
    {
      //Move up.
      this->currentStep++;
      //If out of bounds flip direction.
      if (this->currentStep >= MAP_LINES)
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

    this->servo->SetAngle(DEGREES_PER_STEP*this->currentStep);
    usleep(DELAY_PER_STEP);
    this->SetMap();
}

uint16_t* MappingLogic::GetMap()
{
  return this->distanceMap;
}

void MappingLogic::SetMap()
{
  this->distanceMap[this->currentStep] = this->uart->ReturnDistance();
}

void MappingLogic::InitMappingLogic()
{
  if (wiringPiSetup () == -1)
  {
    printf("failed to setup");
    exit (1);
  }
  this->servo = new Servo(SERVO_PIN, SERVO_MIN_DEGREE, SERVO_MAX_DEGREE, SERVO_HALF_DEGREE);
  this->uart = new Uart();
  this->uartThread = new ThreadHandler<Uart*>(RunLidar, this->uart);
}



