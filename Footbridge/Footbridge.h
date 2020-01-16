#ifndef Footbridge_h
#define Footbridge_h

#include "Arduino.h"

class Footbridge
{
  public:
    Footbridge(int, int); 
    void redLight();
    void greenLight();
    void noLight();
  private:
    int green;
    int red;
};

#endif