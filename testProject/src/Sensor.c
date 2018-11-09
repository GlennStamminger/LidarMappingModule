#include <stdio.h>
#include "errorchecker.h"
#include "driver/uart.h"

uart_config_t uartConfig;

/*void SetUartConfig(int baudrate, enum databits, enum parity, enum stopbit, enum flowcontrol, bool refticks)
{
  uartConfig.baud_rate = baudrate;
  uartConfig.data_bits = uartDataBit.databits;
  uartConfig.parity    = UART_PARITY;
  uartConfig.stop_bits = UART_STOP_BITS_1;
  uartConfig.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
  uartConfig.use_ref_tick = true;
}*/