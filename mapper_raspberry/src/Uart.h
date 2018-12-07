/**
 * @file Uart.h
 * @author Glenn Stamminger
 * @brief protocol to read data from a uart sensor
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>


#ifndef UART_H
#define UART_H

class Uart
{
  public:
    Uart(int TXpin);
    ~Uart();
    void ReadUartByte();
    //uint8_t ReadTFMiniLidar(int sensor);
  private:
    uint8_t measuredDistance;
    int TXpin;
};

#endif