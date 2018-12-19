/**
 * @file Pwm.cpp
 * @author Lars Bloemers & Juul Bloemers
 * @brief 
 * @version 0.1
 * @date 2018-11-22
 * 
 * @copyright Copyright (c) 2018
 * 
 */
#include "Pwm.h"

#define SECOND_TO_MICRO(SECONDS) (SECONDS * 1000000)

//////////////////////////////
// Fields
//////////////////////////////

Pwm *Pwm::instance = 0;


//////////////////////////////
// Methods
//////////////////////////////

Pwm* Pwm::GetInstance()
{
    if(Pwm::instance == nullptr) 
    {

        //Create instance.
        Pwm::instance = new Pwm;
    }
    return Pwm::instance;
}

int8_t Pwm::Init(double frequency, uint16_t prescaler)
{
    this->prescaler = prescaler;
    this->tickTimeMicro = SECOND_TO_MICRO(1.0f / frequency);
    return 0;
}

int8_t Pwm::InitPin(uint8_t pin, uint16_t initialValue)
{
    //If pin found return -1;
    if(this->pins.find(pin) != this->pins.end()) return -1;

    //Set pin mode.
    pinMode(pin, OUTPUT);

    //Add pin.
    this->pins.insert(std::pair<uint8_t, uint16_t>(pin, initialValue));

    //Return no error.
    return 0;
}

int8_t Pwm::UnInitPin(uint8_t pin) 
{
    //Get pin.
    auto pinIt = this->pins.find(pin);

    //If pin found return -1;
    if(pinIt != this->pins.end()) return -1;

    //Remove pin.
    this->pins.erase(pinIt);

    return 0;
}

int8_t Pwm::SetDutyCycle(uint8_t pin, uint16_t dutyCycle) 
{
    //Get pin.
    auto pinIt = this->pins.find(pin);

    //If pin found return -1;
    if(pinIt == this->pins.end()) return -1;

    //Set duty cycle.
    pinIt->second = dutyCycle;

    return 0;
}

void Pwm::Update()
{
    //Check if time is over
    if (micros() - this->lastTimePulsed >= (this->tickTimeMicro / this->prescaler))
    {
        //Set last time pulsed.
        this->lastTimePulsed = micros();

        //Increment tick.
        this->currentTick++;

        //Reset current tick if needed.
        if(this->currentTick > this->prescaler) this->currentTick = 0;

        //Run tick.
        this->PwmTick();
    }
}


//////////////////
// Private methods
//////////////////

void Pwm::PwmTick()
{
    for(auto& item : this->pins) 
    {
        if(this->currentTick > item.second) digitalWrite(item.first, LOW);
        else digitalWrite(item.first, HIGH);
    }
}