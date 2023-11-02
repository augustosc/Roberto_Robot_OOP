/*!
 * @file Radar.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */

#include "Radar.h"

namespace RADAR
{

  //"""""""""""""""""""""""" constructor definition

  Radar::Radar(const uint8_t trigPin, const uint8_t echoPin, const int servoPin, const int pulseMin, const int pulseMax)
      : ultrasonic{trigPin, echoPin}, m_servoPin{servoPin}, m_pulseMin{pulseMin}, m_pulseMax{pulseMax}
  {
    //ATTENTION:
    // do not attach servo inside class constructor
    // attaching the servo inside the main script setup()
  }

  //""""""""""""""""""""""""public member functions

  const float Radar::getDistanceAhead(int _delay)
  {
    servo.write(m_Position.head);
    delay(_delay);
    return ultrasonic.getDistance();
  }


  //""""""""""""""""""""""""

  const float Radar::getDistanceRight(int _delay)
  {
    servo.write(m_Position.right);
    delay(_delay);
    return ultrasonic.getDistance();
  }


  //""""""""""""""""""""""""

  const float Radar::getDistanceDiagRight(int _delay)
  {
    servo.write(m_Position.diagRight);
    delay(_delay);
    return ultrasonic.getDistance();
  }


  //""""""""""""""""""""""""

  const float Radar::getDistanceLeft(int _delay)
  {
    servo.write(m_Position.left);
    delay(m_servoDelay);
    return ultrasonic.getDistance();
  }


  //""""""""""""""""""""""""

  const float Radar::getDistanceDiagLeft(int _delay)
  {
    servo.write(m_Position.diagLeft);
    delay(_delay);
    return ultrasonic.getDistance();
  }


  //"""""""""""""""""""""""" servo methods

  const int Radar::moveServo(int angle)
  {
    servo.write(angle);
    return servo.read();
  }


  //""""""""""""""""""""""""

  void Radar::attach()
  {
    m_servoID = servo.attach(m_servoPin, m_pulseMin, m_pulseMax);
  }


  //""""""""""""""""""""""""

  void Radar::detach()
  {
    servo.detach();
  }


  //""""""""""""""""""""""""

  bool Radar::isAttached()
  {
    return servo.attached();
  }


  //""""""""""""""""""""""""

  int Radar::getServoID()
  {
    return m_servoID;
  }
  

  //""""""""""""""""""""""""

  void Radar::lookAhead()
  {
    moveServo(m_Position.head);
    delay(m_servoDelay);
  }

} // namespace RADAR
