#include <stdio.h>
#include "MappingLogic.h"
#include "Pwm.h"
#include "ThreadHandler.h"
#include <iostream>

#define SECOND_TO_MICRO(SECONDS) (SECONDS * 1000000)

double frequency = 115200;
uint16_t currentTick;
uint64_t lastTimePulsed;
uint16_t prescaler = 8;
double tickTimeMicro = SECOND_TO_MICRO(1.0f / frequency)/prescaler ;
uint8_t previousByte;

int main(int argc, char *argv[])
{  
  if (wiringPiSetup () == -1)
  {
    printf("failed to setup");
    exit (1);
  }
  pinMode(1, INPUT);
        
  while(1)
  {
     //Check if time is over
    if (micros() - lastTimePulsed >= tickTimeMicro)
    {
      //Set last time pulsed.
      lastTimePulsed = micros();
      std::cout<<"micros: "<<tickTimeMicro<<std::endl;
      //Increment tick.
      currentTick++;

      //Reset current tick if needed.
      if(currentTick > prescaler) currentTick = 0;
      
      
  }
}
 return 0;
}
