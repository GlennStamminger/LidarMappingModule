/////////////////////////
//CABLE CONFIGURATION
/////////////////////////
/**
 * ARDUINO:
 * green---------->ground
 * blue----------->5v
 * SERVO:
 * orange--->gray->GPIO18
 * red---->purple->5V
 * brown--->white->ground
 * SENSOR:
 * yellow----->TX->GPIO5
 * white------>RX->GPIO4
 * red------------>5V
 * black---------->ground
 */

/////////////////////////
//INCLUDES
/////////////////////////
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "errorchecker.h"
#include "driver/uart.h"
#include "Sensor.h"
#include "Servo.h"
#include "driver/i2c.h"

/////////////////////////
//DEFINITION
/////////////////////////
#define SERVO_MIN_PULSEWIDTH 450      //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2450     //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 180          //Maximum angle the servo can rotate
#define SERVO_GPIO 18                 //servo control gpio
#define SENSOR_TXD  (GPIO_NUM_4)      //transmit gpio
#define SENSOR_RXD  (GPIO_NUM_5)      //recieve gpio
#define SENSOR_RTS  (GPIO_NUM_22)     //request to send gpio
#define SENSOR_CTS  (GPIO_NUM_23)     //clear to send gpio
#define SENSOR_PORT UART_NUM_1        //uart port
#define BUF_SIZE (128)                //buffer size

/////////////////////////
//VARIABLES
/////////////////////////
uint8_t measuredDistance = 0;
uint8_t distanceMap[180];
uint32_t pulse, angle;

/////////////////////////
//SENSOR CONTROL
/////////////////////////
void SensorTask(void *arg)
{ 
  //set uart parameters
  uart_config_t uart_config = SetUartConfigLidar();

  /* configure parameters of the uart driver,
  * communication pins and install the driver */
  ESP_ERROR_CHECK(uart_param_config(SENSOR_PORT, &uart_config));
  ESP_ERROR_CHECK(uart_set_pin(SENSOR_PORT, SENSOR_TXD, SENSOR_RXD, SENSOR_RTS, SENSOR_CTS));
  ESP_ERROR_CHECK(uart_driver_install(SENSOR_PORT, BUF_SIZE * 2, 0, 0, NULL, 0));

  while (1) 
  {
    //read data from the uart pin
    measuredDistance = MeasureDistance(SENSOR_PORT);
    distanceMap[angle] = measuredDistance;
  }  
}

/////////////////////////
//SERVO CONTROL
/////////////////////////
void ServoTask(void *arg)
{
  //set pin and configure pwm settings
  SetServoPin(SERVO_GPIO);
  mcpwm_config_t pwm_config = SetMcpwmConfiguration();
  ConfigureMcpwm(pwm_config);

  while (1) 
  {
    for (angle = 0; angle < SERVO_MAX_DEGREE; angle++)
    {
      printf("Distance: %d | Angle: %d\n",distanceMap[angle], angle);
      //calculate pulsewidth at current angle
      pulse = CalculatePulseWidth(angle, SERVO_MAX_PULSEWIDTH, SERVO_MIN_PULSEWIDTH, SERVO_MAX_DEGREE);
      //set servo to current angle
      SetAngle(pulse);           
    }
    vTaskDelay(5);
    for(angle = SERVO_MAX_DEGREE -1; angle > 0; angle--)
    {
      printf("Distance: %d | Angle: %d\n",distanceMap[angle], angle);
      //calculate pulsewidth at current angle
      pulse = CalculatePulseWidth(angle, SERVO_MAX_PULSEWIDTH, SERVO_MIN_PULSEWIDTH, SERVO_MAX_DEGREE);
      //set servo to current angle
      SetAngle(pulse);
    }
  }
}

/////////////////////////
//MAIN
/////////////////////////
void app_main()
{
  printf("Initialising mapping module.......\n");
  //functional
  xTaskCreate(ServoTask, "servo_control", 4096, NULL, 5, NULL);
  //functional
  xTaskCreate(SensorTask, "sensor_control", 4096, NULL, 5, NULL);
}