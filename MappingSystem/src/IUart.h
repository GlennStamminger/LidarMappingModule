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
    virtual ~IUart(){};

    /**
     * @brief Get the Tf Mini Distance object
     * 
     * @return the measured distance
     */
    virtual void TfMiniDistance() = 0;

    virtual const uint16_t& ReturnDistance() const = 0;
};

#endif