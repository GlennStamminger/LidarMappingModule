//TEMP CABLE CONFIGURATION LIST
/**
 * ARDUINO:
 * green = ground
 * blue = 5v
 * SERVO:
 * orange = gray = GPIO18
 * red = purple = 5V
 * brown = white = ground
 * SENSOR:
 * yellow = TX = UNDECIDED 
 * white = RX =  UNDECIDED
 * red = 5V
 * black = ground
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "errorchecker.h"
#include "driver/uart.h"


#define SERVO_MIN_PULSEWIDTH 450 //Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2450 //Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 180 //Maximum angle the servo can rotate
#define SENSOR_TXD  (GPIO_NUM_4)
#define SENSOR_RXD  (GPIO_NUM_5)
#define SENSOR_RTS  (GPIO_NUM_22)
#define SENSOR_CTS  (GPIO_NUM_23)


///////////////////
//SENSOR CONTROL
//////////////////


#define BUF_SIZE (128)

static void measure_task()
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config;
    uart_config.baud_rate = 115200;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity    = UART_PARITY;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.use_ref_tick = true;

    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, SENSOR_TXD, SENSOR_RXD, SENSOR_RTS, SENSOR_CTS));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0));

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        uart_read_bytes(UART_NUM_1, data, BUF_SIZE, 100);
        printf("%d\n",data[0]+data[1]);
    }
    free(data);
}
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
    printf("Testing mapping module.......\n");
    //xTaskCreate(mcpwm_servo_control, "mcpwm_servo_control", 4096, NULL, 5, NULL);
    xTaskCreate(measure_task, "uart_sensoring", 4096, NULL, 10, NULL);
}