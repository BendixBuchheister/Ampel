#ifndef trafficLight_h
#define trafficLight_h

#include "Arduino.h"

class trafficLight
{
  public:
    trafficLight(int, int, int); 
    void redLight();
    void greenLight();
    void yellowLight();
    void redYellowLight();
    void noLight();
  private:
    int green;
    int yellow;
    int red;
};

#endif