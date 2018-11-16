#include <stdio.h>
#include "driver/uart.h"
#include "Sensor.h"

//configures the uart with default settings needed for a grove TF mini lidar
uart_config_t SetUartConfigLidar()
{
  uart_config_t lidarDefaultConfig;
  lidarDefaultConfig.baud_rate = 115200;
  lidarDefaultConfig.data_bits = UART_DATA_8_BITS;
  lidarDefaultConfig.parity    = UART_PARITY;
  lidarDefaultConfig.stop_bits = UART_STOP_BITS_1;
  lidarDefaultConfig.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
  lidarDefaultConfig.use_ref_tick = true;
  return lidarDefaultConfig;
}

//get current distance
int MeasureDistance(int uartPort)
{
  int reader;
  unsigned int t1 = 0;
  unsigned int t2 = 0;
  uint8_t fillerArray[1];
  reader = uart_read_bytes(uartPort, fillerArray, 1, 100);
  if(reader == 1 && fillerArray[0] == 0x59)
  {
    reader =  uart_read_bytes(uartPort, fillerArray, 1, 100);
    if(reader == 1  && fillerArray[0] == 0x59)
    {
      //printf("complete frame detected\n");
      reader =  uart_read_bytes(uartPort, fillerArray, 1, 100);
      if(reader != 1)
      {
        printf("cannot read distance\n");
        return 0;
      }
      t1 = fillerArray[0];
      reader = uart_read_bytes(uartPort, fillerArray, 1, 100);
      t2 = fillerArray[0];
      if(reader == 1)
      {
        t2 <<= 8;
        t2 += t1;
      }
      else
      {
        printf("cannot read distance\n");
        return 0;
      }  
    }
    for(int i = 0; i<5; i++)
    {
      reader = uart_read_bytes(uartPort, fillerArray, 1, 100);
    }
    return t2;
  }
  printf("incomplete frame\n");
  return 0;
  
}