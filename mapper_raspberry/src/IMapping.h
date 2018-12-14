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
    virtual std::vector<int> GetMap() = 0;

    //initialises the mapping
    virtual void Update() = 0;
};

#endif
