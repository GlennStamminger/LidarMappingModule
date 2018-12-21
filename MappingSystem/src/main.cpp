/**
 * @file main.cpp
 * @author Glenn Stamminger
 * @brief example main class to use the mappinglogic
 * @version 0.1
 * @date 2018-12-19
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "MappingLogic.h"
#include "ThreadHandler.h"

//Instance of mappinglogic class and distance array.
MappingLogic *myMapper = new MappingLogic();
uint16_t* map;

//Create MappingLogic thread.
ThreadHandler<MappingLogic*>* mappingThread;

//Loop to update the pwm.
void PwmUpdate(Pwm* pwm) 
{
  while(1) pwm->Update();
}

//Loop to update the map.
void MappingLogicUpdate(MappingLogic* mapper)
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
    //Update map.
    map = myMapper->GetMap();
  }
  delete mappingThread;
  delete myMapper;
  return 0;
}

