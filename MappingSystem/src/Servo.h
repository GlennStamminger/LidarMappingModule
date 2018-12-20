/**
 * @file Servo.h
 * @author Juul Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-11-22
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef SERVO_H
#define SERVO_H

///////////////////////////////////////
// INCLUDES
///////////////////////////////////////

#include <stdint.h>
#include <stdexcept>

#include <wiringPi.h>

#include "Pwm.h"


///////////////////////////////////////
// DEFINES
///////////////////////////////////////

#define SERVO_PWM_FREQUENCY (50)
#define SERVO_PWM_PRESCALER (1024)


///////////////////////////////////////
// CLASSES
///////////////////////////////////////

class Servo {

public:
  Servo(uint8_t pin, uint8_t minAngle, uint8_t maxAngle, uint8_t initialAngle);
  ~Servo();

  uint8_t GetAngle();

  void SetAngle(uint8_t angle);

private:
  uint8_t pin;
  uint8_t angle;
  uint8_t minAngle;
  uint8_t maxAngle;

};

#endif