/*!
 * @file Car.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#include "Car.h"
#include "MotorGpio.h"

namespace CAR 
{
    //"""""""""""""""""""""""" constructor definition

    Car::Car()
      : MD{MotorGpio::mDpin1, MotorGpio::mDpin2, MotorGpio::mDhab}
      , ME{MotorGpio::mEpin1, MotorGpio::mEpin2, MotorGpio::mEhab}
    {
        // Adjust motor speed
        MD.setMotorSpeed(m_rightMotorSpeed);
        ME.setMotorSpeed(m_leftMotorSpeed);
    }



  //"""""""""""""""""""""""" public move member functions

  void Car::moveForward()
  {
    MD.forward();
    ME.forward();
  }

  //""""""""""""""""""""""""

  void Car::moveBackward()
  {
    MD.backward();
    ME.backward();
  }

  //""""""""""""""""""""""""

  void Car::stopMove()
  {
    MD.off();
    ME.off();
  }

  //""""""""""""""""""""""""

  void Car::turnLeft()
  {
    this->stopMove();
    delay(500);
    MD.forward(m_currentTurnSpeed);
    ME.backward(m_currentTurnSpeed);
    delay(m_currentTurnInterval);
    this->stopMove();
  }

  //""""""""""""""""""""""""

  void Car::turnRight()
  {
    this->stopMove();
    delay(500);
    MD.backward(m_currentTurnSpeed);
    ME.forward(m_currentTurnSpeed);
    delay(m_currentTurnInterval);
    this->stopMove();
  }



  //"""""""""""""""""""""""" public motor configuration member functions

  void Car::setTurnSpeed(int newTurnSpeed)
  {
    m_currentTurnSpeed = newTurnSpeed;
  }

  //""""""""""""""""""""""""

  void Car::resetTurnSpeed()
  {
    m_currentTurnSpeed = m_defaultTurnSpeed;
  }

  //""""""""""""""""""""""""

  int Car::getTurnSpeed()
  {
    return m_currentTurnSpeed;
  }

  //""""""""""""""""""""""""

  void Car::setTurnInterval(int newInterval)
  {
    m_currentTurnInterval = newInterval;
  }

  //""""""""""""""""""""""""

  void Car::resetTurnInterval()
  {
    m_currentTurnInterval = m_defaultTurnInterval;
  }

  //""""""""""""""""""""""""

  const int Car::getTurnInterval()
  {
    return m_currentTurnInterval;
  }

  //""""""""""""""""""""""""

  void Car::setMotorSpeed(int motorID, int newSpeed)
  {
    switch (motorID)
    {
    case rightMotor:
      MD.setMotorSpeed(newSpeed);
      break;

    case leftMotor:
      ME.setMotorSpeed(newSpeed);
      break;

    case bothMotors:
      MD.setMotorSpeed(newSpeed);
      ME.setMotorSpeed(newSpeed);
    }
  }

  //""""""""""""""""""""""""

  void Car::setMotorSpeed(int newSpeed)
  {
    setMotorSpeed(bothMotors, newSpeed);
  }

  //""""""""""""""""""""""""

  void Car::resetMotorSpeed(int motorID)
  {

    switch (motorID)
    {
    case rightMotor:
      MD.resetMotorSpeed();
      break;

    case leftMotor:
      ME.resetMotorSpeed();
      break;

    case bothMotors:
      MD.resetMotorSpeed();
      ME.resetMotorSpeed();
    }
  }

  //""""""""""""""""""""""""

  const int Car::getMotorSpeed(int motorID)
  {
    switch (motorID)
    {

    case rightMotor:
      return MD.getMotorSpeed();
      break;

    case leftMotor:
      return ME.getMotorSpeed();
      break;

    case bothMotors:
      if (MD.getMotorSpeed() == ME.getMotorSpeed())
        return MD.getMotorSpeed();
      else
        return 130;
    }
    return 0;
  }

}