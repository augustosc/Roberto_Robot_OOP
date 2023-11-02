/*!
 * @file Motor.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#ifndef _MOTOR_H
#define _MOTOR_H

#include "Arduino.h"

namespace MOTOR
{

  //""""""""""""""""""""""""class

  /// @brief class to control DC motor by L298D driver
  class Motor
  {

  
  //"""""""""""""""""""""""" construtor declaration
  public:
    /// @brief constructor motor object
    /// @param in1 pin1 to L298D
    /// @param in2 pin2 to L298D
    /// @param inpwm pin pwm to L298D
    Motor(const uint8_t in1, const uint8_t in2, const uint8_t inpwm);



    //"""""""""""""""""""""""" public member functions

    /// @brief move motor forward at current speed
    void forward();

    /// @brief move motor forward at specified speed
    void forward(int speed);

    /// @brief move motor backward at current speed
    void backward();

    /// @brief move motor backward at specified speed
    void backward(int speed);

    /// @brief turn off motor
    void off();

    /// @brief set new speed to motor
    void setMotorSpeed(int newSpeed);

    /// @brief reset motor to default speed
    void resetMotorSpeed();

    /// @brief get motor speed
    /// @return current motor speed
    const int getMotorSpeed();



  //"""""""""""""""""""""""" private data members
  private:
    const int m_defaultSpeed{120};           ///< motor default speed
    int m_currentMotorSpeed{m_defaultSpeed}; ///< motor current speed
    const uint8_t m_in1Pin{};                ///< L298 control pin 1
    const uint8_t m_in2Pin{};                ///< L298 control pin 2
    const uint8_t m_inpwmPin{};              ///< Ld98 PWM pin

  };
} // namespace MOTOR

#endif //_MOTOR_H
