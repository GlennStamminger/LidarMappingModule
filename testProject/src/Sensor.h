#include <driver/uart.h>
#ifndef SENSOR_H
#define SENSOR_H

/**
 * @brief Set the Uart Config Lidar object
 * 
 * @return uart_config_t 
 */
uart_config_t SetUartConfigLidar();

/**
 * @brief 
 * 
 * @param uartPort 
 * @return int 
 */
int MeasureDistance(int uartPort);

#endif