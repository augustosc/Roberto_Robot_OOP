/*!
 * @file Motor.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#include "Motor.h"

namespace MOTOR
{

  //"""""""""""""""""""""""" construtor definition

  Motor::Motor(const uint8_t in1Pin, const uint8_t in2Pin, const uint8_t inpwmPin)
      : m_in1Pin{in1Pin}, m_in2Pin{in2Pin}, m_inpwmPin{inpwmPin}
  {
    pinMode(m_in1Pin, OUTPUT);
    pinMode(m_in2Pin, OUTPUT);
    pinMode(m_inpwmPin, OUTPUT);
  }

  //"""""""""""""""""""""""" forward methods
  void Motor::forward()
  {
    analogWrite(m_inpwmPin, m_currentMotorSpeed);

    digitalWrite(m_in1Pin, HIGH);
    digitalWrite(m_in2Pin, LOW);
  }

  //""""""""""""""""""""""""

  void Motor::forward(int speed)
  { // overload used for Roberto turn methods
    analogWrite(m_inpwmPin, speed);

    digitalWrite(m_in1Pin, HIGH);
    digitalWrite(m_in2Pin, LOW);
  }

  //"""""""""""""""""""""""" backward methods
  void Motor::backward()
  {
    analogWrite(m_inpwmPin, m_currentMotorSpeed);

    digitalWrite(m_in1Pin, LOW);
    digitalWrite(m_in2Pin, HIGH);
  }

  //""""""""""""""""""""""""

  void Motor::backward(int speed)
  {
    analogWrite(m_inpwmPin, speed);

    digitalWrite(m_in1Pin, LOW);
    digitalWrite(m_in2Pin, HIGH);
  }

  //"""""""""""""""""""""""" off
  void Motor::off()
  {
    digitalWrite(m_inpwmPin, LOW);

    digitalWrite(m_in1Pin, LOW);
    digitalWrite(m_in2Pin, LOW);
  }

  //"""""""""""""""""""""""" speed methods
  void Motor::setMotorSpeed(int newSpeed)
  {
    m_currentMotorSpeed = newSpeed;
  }

  //""""""""""""""""""""""""

  void Motor::resetMotorSpeed()
  {
    m_currentMotorSpeed = m_defaultSpeed;
  }

  //""""""""""""""""""""""""

  const int Motor::getMotorSpeed()
  {
    return m_currentMotorSpeed;
  }
} // namespace MOTOR
