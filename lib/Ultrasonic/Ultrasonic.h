#ifndef _HCSR04_H
#define _HCSR04_H

#include "Arduino.h"

/// @brief Ultrasonic class to measure obstacle distances
class Ultrasonic {

  private:
    int m_trigPin;
    int m_echoPin;
  
  public:
    Ultrasonic(){};
    Ultrasonic(int trigPin, int echoPin);

    /// @brief get distance from obstacle
    /// @return distance in cm
    float getDistance ();
};

#endif  //_HCSR04_H
