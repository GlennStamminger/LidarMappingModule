#ifndef IMAPPING_H
#define IMAPPING_H

#include <vector>
#include <wiringPi.h>
#include <wiringSerial.h>

class IMapping
{
  public:
    virtual ~IMapping(){};

    /**
    *checks if communication is succesfull
    *1 = success | 0 = failure
    */
    virtual int GetStatus() = 0;

    //  Returns the distance given an angle
    virtual int GetDistanceAtAngle(int angle) = 0;

    //  Returns array with the distances of all visible objects
    virtual std::vector<int> GetMap() = 0;

    //initialises the mapping
    virtual void Update() = 0;
};

#endif
