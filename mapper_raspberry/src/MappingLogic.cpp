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
    : distance(0)
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
  //has to become delta time

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

    this->SetMap();
    this->servo->SetAngle(this->currentStep);
    usleep(3600);
}

uint16_t* MappingLogic::GetMap()
{
  return this->distanceMap;
}

void MappingLogic::SetMap()
{
  if(this->currentStep == 1)
  {
    distanceMap[0] = this->uart->ReturnDistance();
  }
  else if(this->currentStep == 45)
  {
    distanceMap[1] = this->uart->ReturnDistance();
  }
  else if(this->currentStep == 90)
  {
    distanceMap[2] = this->uart->ReturnDistance();
  }
  else if(this->currentStep == 135)
  {
    distanceMap[3] = this->uart->ReturnDistance();
  }
  else if(this->currentStep == 179)
  {
    distanceMap[4] = this->uart->ReturnDistance();
  }
  else
  {
    //irrelevant angles
    //std::cout<<"readirrelevant: "<<this->uart->ReturnDistance()<<std::endl;
  }
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



