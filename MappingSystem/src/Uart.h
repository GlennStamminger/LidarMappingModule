/**
 * @file Uart.h
 * @author Glenn Stamminger
 * @brief header file for uart class
 * @version 0.1
 * @date 2018-12-06
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef UART_H
#define UART_H
#include "IUart.h"

class Uart : public IUart
{
private:
  int8_t currentByte;
  uint8_t readStartSymbols;
  uint8_t readDataSymbols;
  uint16_t recievedDistance;
  uint16_t recievedBuffer;
  int fd;
  bool isReadingData;
  void InitSerial();
  void DeInitSerial();

public:
  Uart();
  ~Uart();
  void TfMiniDistance();
  const uint16_t& ReturnDistance() const;
};

#endif