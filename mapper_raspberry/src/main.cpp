
/*
 * serialRead.c:
 *	Example program to read bytes from the Serial line
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <wiringSerial.h>

uint8_t currentByte = 0;
uint8_t readStartSymbols = 0;
uint8_t readDataSymbols = 0;
int tester = 0;
uint16_t recievedDistance;

bool isReadingData = false;

int main ()
{
  int fd ;

  if ((fd = serialOpen ("/dev/ttyS0", 115200)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

// Loop, getting and printing characters
  while(1)
  {
    while(serialDataAvail(fd) > 0)
    {
      currentByte = serialGetchar(fd);
      if(isReadingData)
      {
        std::cout<<"1"<<std::endl;
        readDataSymbols++;
        if(readDataSymbols == 1)
        {
          recievedDistance = currentByte;
          std::cout<<"2"<<std::endl;
        }
        else if(readDataSymbols >= 2)
        {
          recievedDistance |= (static_cast<uint16_t>(currentByte) << 8);
          std::cout<<"3"<<std::endl;
          tester++;
          isReadingData = false;
        }
      }
      if(currentByte == 0x59)
      {
        std::cout<<"4"<<std::endl;
        readStartSymbols++;
        if(readStartSymbols >= 2)
        {
          std::cout<<"5"<<std::endl;
          readStartSymbols = 0;
          readDataSymbols = 0;
          isReadingData = true;
        }
      }
    }
  }
  serialClose(fd);
}

