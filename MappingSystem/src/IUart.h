/**
 * @file IUart.h
 * @author Glenn Stamminger
 * @brief interface for the uart class
 * @version 0.1
 * @date 2018-12-21
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef IUART_H
#define IUART_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <wiringSerial.h>


class IUart
{
  public:

    //Destructor.
    virtual ~IUart(){};

    /**
     * @brief Starts sequence to read distance from the Grove TF mini lidar once.
     * 
     */
    virtual void TfMiniDistance() = 0;

    /**
     * @brief Give the distance.
     * 
     * @returns the measured distance.
     */
    virtual const uint16_t& ReturnDistance() const = 0;
};

#endif