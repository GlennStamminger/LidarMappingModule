/**
 * @file Pwm.h
 * @author Lars Bloemers & Juul Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-11-22
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#ifndef PWM_H
#define PWM_H

///////////////////////////////////////
// INCLUDES
///////////////////////////////////////

#include <iostream>
#include <stdint.h>
#include <map>

#include <wiringPi.h>

///////////////////////////////////////
// CLASSES
///////////////////////////////////////

class Pwm 
{
  public:
    static Pwm* GetInstance();

    int8_t Init(double frequency, uint16_t prescaler);
    int8_t InitPin(uint8_t pin, uint16_t initialValue);
    int8_t UnInitPin(uint8_t pin);
    int8_t SetDutyCycle(uint8_t pin, uint16_t dutyCycle);

    void Update();

  private:
    static Pwm* instance;

    std::map<uint8_t, uint16_t> pins;

    uint64_t lastTimePulsed;
    uint16_t prescaler;
    uint16_t currentTick;
    uint64_t tickTimeMicro;

    void PwmTick();
};

#endif