/**
 * @file main.cpp
 * @author Glenn Stamminger
 * @brief 
 * @version 0.1
 * @date 2018-12-19
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "MappingLogic.h"
#include "ThreadHandler.h"

MappingLogic *myMapper = new MappingLogic();
ThreadHandler<MappingLogic*>* mappingThread;
uint16_t* map;

void PwmUpdate(Pwm* pwm) 
{
  while(1) pwm->Update();
}

static void MappingLogicUpdate(MappingLogic* mapper)
{
  std::cout<<"map loop"<<std::endl;
  while(1)
  {
    mapper->Update();
  }
}

int main ()
{
  mappingThread = new ThreadHandler<MappingLogic*>(MappingLogicUpdate, myMapper);
  //Init pwm.
  Pwm::GetInstance()->Init(50, 1024);

  //Create pwm thread.
  ThreadHandler<Pwm*> thread(PwmUpdate, Pwm::GetInstance());
  while(1)
  {
    map = myMapper->GetMap();
  }
  delete mappingThread;
  delete myMapper;
  return 0;
}

