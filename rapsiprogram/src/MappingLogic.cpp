#include "MappingLogic.h"

//Definitions
#define SENSOR_TX 16
#define SERVO_PIN 15
#define SERVO_MAX_DEGREE 180

//Constructor
MappingLogic::MappingLogic()
  :measuredDistance(0)
{
  this->servo = new Servo(SERVO_PIN, 0, 180, 90);
  this->uart = new Uart(SENSOR_TX);

  if(GetStatus() == 1)
  {
    printf("data is available\n");
    Update();
  }
}

//Variables
std::vector<int> distanceMap(SERVO_MAX_DEGREE);


void MappingLogic::Update()
{
  pinMode(SENSOR_TX, INPUT);
  //If dalta time passed. 1 is temp, has to be delta time later
  if(1)
  {
    if(this->stepMovingUp)
    {
      //Move up.
      this->currentStep++;

      //If out of bounds flip direction.
      if(this->currentStep >= 179) 
      {
        this->stepMovingUp = false;
      }
    }
    else 
    {
      //Move down.
      this->currentStep--;

      //If out of bounds flip direction.
      if(this->currentStep <= 0) 
      {
        this->stepMovingUp = true;
      }
    }

    printf("%i current step: \n", this->currentStep);
    this->uart->ReadUartByte();
    this->servo->SetAngle(this->currentStep);
    usleep(3600);
  }

  /*
  pinMode(SENSOR_TX, INPUT);
  while(1)
  {
    int step = 0;
    printf("forward\n");
    for(std::vector<int>::iterator i = distanceMap.begin(); i != distanceMap.end(); i++)
    {
      //printf("%d",digitalRead(SENSOR_TX));
      //measuredDistance = Sensor::ReadDistance();
      this->servo->SetAngle(step);
      //i = measuredDistance;
      step++;
      usleep(3600);
    }
    
    printf("backward\n");
    for(std::vector<int>::iterator j = distanceMap.end(); j != distanceMap.begin(); j--)
    {
      //printf("%d",digitalRead(SENSOR_TX));
      //measuredDistance = Sensor::ReadDistance();
      this->servo->SetAngle(step);
      //j = measuredDistance;
      step --;
      usleep(3600);
    }
    
  }
  */
}


int MappingLogic::GetDistanceAtAngle(int angle) 
{  
  if(angle >= 0 && angle <SERVO_MAX_DEGREE)
  {
    return distanceMap[angle];
  }
  return 0;
}

int MappingLogic::GetStatus() 
{ 
  

  int fd;

  fd = serialOpen("/dev/ttyAMA0", 115200);
  if(fd < 0)
  {
    printf("ERROR: Could not open serial.\n");
    return fd;
  }
  
  return 1;
}

std::vector<int> MappingLogic::GetMap()
{ 
  return distanceMap; 
}

/*void testFunction()
{
  while(1)
  {
    int number = digitalRead(SENSOR_TX);
    printf("%d",number);
  }
}*/

