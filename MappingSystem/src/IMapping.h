#ifndef IMAPPING_H
#define IMAPPING_H

#include <vector>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <vector>
#include "ThreadHandler.h"
#include "Servo.h"
#include "Uart.h"


class IMapping
{
  public:
    virtual ~IMapping(){};

    //  Returns array with the distances of all visible objects
    virtual uint16_t* GetMap() = 0;

    //initialises the mapping
    virtual void Update() = 0;

    //assigns values to the map
    virtual void SetMap() = 0;

    virtual void InitMappingLogic() = 0;
};

#endif
