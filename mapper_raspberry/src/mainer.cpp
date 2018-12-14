#include <stdio.h>
#include "MappingLogic.h"
#include "Pwm.h"
#include "ThreadHandler.h"

void PwmUpdate(Pwm* pwm) 
{
  while(1) pwm->Update();
}

int main(int argc, char *argv[])
{
  

  //Init pwm.
  Pwm::GetInstance()->Init(50, 1024);

  //Create pwm thread.
  ThreadHandler<Pwm*> thread(PwmUpdate, Pwm::GetInstance());

  //int test = 3;
  IMapping *newClass = new MappingLogic();
  newClass->GetStatus();

  while(1)
  {
    newClass->Update();
  }

  return 0;
}

