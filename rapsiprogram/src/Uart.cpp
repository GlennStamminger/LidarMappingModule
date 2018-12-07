/**
 * @file Uart.cpp
 * @author Glenn Stamminger
 * @brief 
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 *
 */
#include "Uart.h"

#define UART_BYTE_ARRAY_SIZE (12)

//Constructor
Uart::Uart(int TXpin)
  :measuredDistance(0), TXpin(TXpin) {}

void Uart::ReadUartByte()
{
  uint16_t fillerarray[UART_BYTE_ARRAY_SIZE];
  for(int i = 0; i < UART_BYTE_ARRAY_SIZE; i++)
  {
    fillerarray[i] = digitalRead(TXpin);
    printf("%d", fillerarray[i]);
  }
  printf("\n");
}

 