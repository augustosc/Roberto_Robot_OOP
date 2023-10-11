#ifndef _HCSR04_H
#define _HCSR04_H

#include "Arduino.h"

namespace ULTRASONIC
{

  /// @brief Ultrasonic class to measure obstacle distances
  class Ultrasonic
  {

  private:
    const uint8_t m_trigPin;            ///< ultrasonic trigger pin
    const uint8_t m_echoPin;            ///< ultrasonic echo pin
    const int m_distMax{150};       ///< max distance measured
    float m_distance{};               ///< measured distance

  public:
  
    Ultrasonic(const uint8_t trigPin, const uint8_t echoPin);

    /// @brief get distance from obstacle
    /// @return distance in cm
    float getDistance();
  };
} // namespace ULTRASONIC

#endif //_HCSR04_H
