#include "esp_attr.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include "Servo.h"

void SetServoPin(int gpioNumber)
{
  //initializes a pin as pwm
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, gpioNumber);
}

uint32_t CalculatePulseWidth(uint32_t currentAngle, int maxPulseWidth, int minPulseWidth, int maxRotation)
{
  uint32_t pulseWidth = 0;
  pulseWidth = (minPulseWidth + (((maxPulseWidth - minPulseWidth) * (currentAngle)) / (maxRotation)));
  return pulseWidth;
}

mcpwm_config_t SetMcpwmConfiguration()
{
  mcpwm_config_t pwmDefaultConfig;
  pwmDefaultConfig.frequency = 50; //frequency = 50Hz = 20ms
  pwmDefaultConfig.cmpr_a = 0;     //duty cycle of PWMxA = 0
  pwmDefaultConfig.cmpr_b = 0;     //duty cycle of PWMxb = 0
  pwmDefaultConfig.counter_mode = MCPWM_UP_COUNTER;
  pwmDefaultConfig.duty_mode = MCPWM_DUTY_MODE_0;
  return pwmDefaultConfig;
}

void ConfigureMcpwm(mcpwm_config_t pwmConfig)
{
  //initialisez the pwm configuration
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwmConfig); 
}

void SetAngle(uint32_t pulse)
{
  //sends to pulsewidth to the servo which sets the angle
  mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, pulse);
}