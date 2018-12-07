#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#ifndef SERVO_H
#define SERVO_H

/**
 * @brief sets a gpio to be used for pwm
 * 
 * @param gpioNumber 
 */
void SetServoPin(int gpioNumber);

/**
 * @brief calculates the pulsewidth for the corresponding angle
 * 
 * @param currentAngle - angle at which the servo currently is at 
 * @param maxPulseWidth - maximum size of the pulse width
 * @param minPulseWidth - minimal size of the pulse width 
 * @param maxRotation - maximum angle the servo can rotate
 * @return calculated pulse width
 */
uint32_t CalculatePulseWidth(uint32_t currentAngle, int maxPulseWidth, int minPulseWidth, int maxRotation);

/**
 * @brief sets the pwm configuration
 * 
 * @return the pwm configuration
 */
mcpwm_config_t SetMcpwmConfiguration();

/**
 * @brief initialisez the configuration on the pwm
 * 
 * @param pwmConfig 
 */
void ConfigureMcpwm(mcpwm_config_t pwmConfig);

/**
 * @brief Sets the angle of the servo
 * 
 * @param pulse 
 */
void SetAngle(uint32_t pulse);

#endif