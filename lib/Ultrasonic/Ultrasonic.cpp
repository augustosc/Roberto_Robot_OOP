/*!
 * @file Ultrasonic.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#include "Ultrasonic.h"

// #define _DEBUG

namespace ULTRASONIC
{
  //"""""""""""""""""""""""" constructor definition

  Ultrasonic::Ultrasonic(const uint8_t trigPin, const uint8_t echoPin)
      : m_trigPin{trigPin}, m_echoPin{echoPin}
  {
    pinMode(m_trigPin, OUTPUT);
    pinMode(m_echoPin, INPUT);
  }

  //""""""""""""""""""""""""member funtion definition

  const float Ultrasonic::getDistance()
  {
    digitalWrite(m_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trigPin, LOW);
    
    m_distance = pulseIn(m_echoPin, HIGH) * 0.01724;
    delay(30);

    if (m_distance > m_distMax)
      m_distance = 30;

#ifdef _DEBUG
    Serial.print("getDistance: ");
    Serial.println(distance);
#endif

    return m_distance;
  }
  
} // namespace ULTRASONIC
