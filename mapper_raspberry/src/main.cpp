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

void MappingLogicUpdate(MappingLogic* mapper)
{
  while(1) mapper->Update();
}

int main ()
{
  //check if this can be removed
  if (wiringPiSetup () == -1)
  {
    printf("failed to setup");
    exit (1);
  }

  ThreadHandler<MappingLogic*> thread(MappingLogicUpdate, myMapper);
  while(1)
  {
    //here is the rest of the code
  }
  delete myMapper;
  return 0;
}

