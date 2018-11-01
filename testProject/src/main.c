#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define SERVO_MIN_PULSEWIDTH 450 //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2450 //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 180 //Maximum angle the servo can rotate

///////////////////
//SENSOR CONTROL
//////////////////

//////////////////
//SERVO CONTROL
/////////////////
static void mcpwm_gpio_initialize()
{
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, 18);    //Set GPIO 18 as PWM0A, to which servo is connected
}

/**
 * @brief Use this function to calcute pulse width for per degree rotation
 *
 * @param  degree_of_rotation the angle in degree to which servo has to rotate
 *
 * @return
 *     - calculated pulse width
 */
static uint32_t servo_per_degree_init(uint32_t degree_of_rotation)
{
    uint32_t cal_pulsewidth = 0;
    cal_pulsewidth = (SERVO_MIN_PULSEWIDTH + (((SERVO_MAX_PULSEWIDTH - SERVO_MIN_PULSEWIDTH) * (degree_of_rotation)) / (SERVO_MAX_DEGREE)));
    return cal_pulsewidth;
}

/**
 * @brief Configure MCPWM module
 */
void mcpwm_servo_control(void *arg)
{
    uint32_t pulse, angle;
    //1. mcpwm gpio initialization
    mcpwm_gpio_initialize();

    //2. initial mcpwm configuration
    printf("Configuring Initial Parameters of mcpwm......\n");
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;    //frequency = 50Hz, i.e. for every servo motor time period should be 20ms
    pwm_config.cmpr_a = 0;    //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;    //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    while (1) {
        for (angle = 0; angle < SERVO_MAX_DEGREE; angle++) {
            printf("Angle of rotation: %d\n", angle);
            pulse = servo_per_degree_init(angle);
            printf("pulse width: %dus\n", pulse);
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pulse);            
        }
        vTaskDelay(5);
        for(angle = SERVO_MAX_DEGREE -1; angle > 0; angle--)
        {
          printf("Angle of rotation: %d\n", angle);
          pulse = servo_per_degree_init(angle);
          printf("pulse width: %dus\n", pulse);
          mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pulse);
        }
        vTaskDelay(5);
    }
}

void app_main()
{
    printf("Testing servo motor.......\n");
    xTaskCreate(mcpwm_servo_control, "mcpwm_servo_control", 4096, NULL, 5, NULL);
}