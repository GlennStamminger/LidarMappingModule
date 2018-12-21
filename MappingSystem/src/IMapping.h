/**
 * @file IMapping.h
 * @author Glenn Stamminger
 * @brief interface for the mappinglogic class
 * @version 0.1
 * @date 2018-12-21
 * 
 * @copyright Copyright (c) 2018
 * 
 */
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

    /**
     * @brief Get the Map object
     * 
     * @returns array with the distances of all visible objects. 
     */
    virtual uint16_t* GetMap() = 0;

    /**
     * @brief Runs the mapping sequence once. 
     * 
     */
    virtual void Update() = 0;

    /**
     * @brief Set the Map object
     * 
     */
    virtual void SetMap() = 0;

    /**
     * @brief Initiate wiring pi and initialise class instances.
     * 
     */
    virtual void InitMappingLogic() = 0;
};

#endif
