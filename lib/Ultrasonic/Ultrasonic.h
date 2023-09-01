#ifndef _HCSR04_H
#define _HCSR04_H

#include "Arduino.h"

class Ultrasonic {

  private:
    int m_trigPin;
    int m_echoPin;
  
  public:
    Ultrasonic(){};
    Ultrasonic(int trigPin, int echoPin);
    float getDistance ();
};

#endif
