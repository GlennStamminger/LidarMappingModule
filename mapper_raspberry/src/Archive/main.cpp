#include <iostream>
#include <unistd.h>

#include <wiringPi.h>

#include "ThreadHandler.h"

#include "Servo.h"
#include "Pwm.h"

void PwmUpdate(Pwm* pwm) 
{
  while(1) pwm->Update();
}

int main(int argc, char** argv)
{
  if(wiringPiSetup() < 0)
  {
    std::cout << "DRIVE_MODULE: Error setting up wiring pi." << std::endl;
    exit(-1);
  }

  //Init pwm.
  Pwm::GetInstance()->Init(50, 1024);

  //Create servos.
  Servo servos[3] = {
    Servo(4, 10, 170, 90),
    Servo(5, 10, 170, 90),
    Servo(6, 10, 170, 90)
  };

  ThreadHandler<Pwm*> thread(PwmUpdate, Pwm::GetInstance());

  while(1) 
  {
    
  }

  return 0;
}