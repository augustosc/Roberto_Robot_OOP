#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H


#include "Arduino.h"


namespace ULTRASONIC
{

  //""""""""""""""""""""""""class

  /// @brief Ultrasonic class to measure obstacle distances
  class Ultrasonic
  {


   //"""""""""""""""""""""""" constructor declaration
  public:

    /// @brief constructor Ultrasonic
    /// @param trigPin ultrasonic trigger pin
    /// @param echoPin ultrasonic echo pin
    Ultrasonic(const uint8_t trigPin, const uint8_t echoPin);



    //"""""""""""""""""""""""" public member function declaration

    /// @brief get distance from obstacle
    /// @return distance in cm
    const float getDistance();



    //"""""""""""""""""""""""" private data members
  private:
    const uint8_t m_trigPin;            ///< ultrasonic trigger pin
    const uint8_t m_echoPin;            ///< ultrasonic echo pin
    const int m_distMax{150};           ///< max distance measured
    float m_distance{};                 ///< measured distance

  };

} // namespace ULTRASONIC

#endif //_ULTRASONIC_H
