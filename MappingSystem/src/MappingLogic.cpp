/**
 * @file MappingLogic.cpp
 * @author Glenn Stamminger
 * @brief class file for the mapping
 * @version 0.1
 * @date 2018-12-21
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "MappingLogic.h"

//Loop to read distance.
static void RunLidar(Uart *uart)
{
  while (1)
  { 
    uart->TfMiniDistance();
  }
}

//Constructor.
MappingLogic::MappingLogic()
{
  this->InitMappingLogic();
}

//Destructor.
MappingLogic::~MappingLogic()
{
  delete this->uartThread;
  delete this->uart;
}

//Update the map and move the servo to the next step.
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

//Return the map.
uint16_t* MappingLogic::GetMap()
{
  return this->distanceMap;
}

//Update the current section the map is on.
void MappingLogic::SetMap()
{
  this->distanceMap[this->currentStep] = this->uart->ReturnDistance();
}

//Initiate setup for mappinglogic.
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



