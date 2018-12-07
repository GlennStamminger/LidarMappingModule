#include <driver/uart.h>
#ifndef SENSOR_H
#define SENSOR_H

/**
 * @brief Sets the uart configuration
 * 
 * @return uart_config_t 
 */
uart_config_t SetUartConfigLidar();

/**
 * @brief measures the distance from the sensor
 * 
 * @param uartPort the port on which the sensor's TX pin is placed 
 * @return the measured distance
 */
uint8_t MeasureDistance(int uartPort);

/**
 * @brief sends the distance to the brain
 * 
 * @param uartPort the port on which the sensor's RX pin is placed
 * @param distance the data to be sent
 */
void SendDistance(int uartPort, uint8_t distance);

#endif