#include <stdio.h>
#include "MappingLogic.h"
#include "Pwm.h"
#include "ThreadHandler.h"

int main(int argc, char *argv[])
{
  if (wiringPiSetup () == -1)
  {
    printf("failed to setup");
    exit (1);
  }
  pinMode(16, INPUT);

  for(;;)
  {
    int filler[12];
      for(int i = 0; i < 12; i ++)
      {
        filler[i] = digitalRead(16);
        printf("%d",filler[i]);
      }
      printf("\n");     
  }
  return 0;
}

