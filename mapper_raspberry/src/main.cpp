
/*
 * serialRead.c:
 *	Example program to read bytes from the Serial line
 *
 */

#include "MappingLogic.h"
#include "ThreadHandler.h"
//ZET DE NIEUWE PWM ER IN
 MappingLogic *myMapper = new MappingLogic();

 void MappingLogicUpdate(MappingLogic* mapper)
 {
   while(1) mapper->Update();
 }

int main ()
{
   ThreadHandler<MappingLogic*> thread(MappingLogicUpdate, myMapper);
   while(1)
   {
     //here is the rest of the code
   }
  delete myMapper;
  return 0;
}

