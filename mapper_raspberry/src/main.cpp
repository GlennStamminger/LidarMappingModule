
/*
 * serialRead.c:
 *	Example program to read bytes from the Serial line
 *
 */

#include "Uart.h"
#include "ThreadHandler.h"

 Uart *myUart = new Uart();

void RunLidar(Uart* uart)
{
  while(1)
  {
    myUart->TfMiniDistance();
  }
}

int main ()
{
  // Loop, getting and printing characters
   ThreadHandler<Uart*> thread(RunLidar, myUart);
   while(1)
   {
     std::cout<<"read: "<<myUart->ReturnDistance()<<std::endl;
   }
  delete myUart;
  return 0;
}

