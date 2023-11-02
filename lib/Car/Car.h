/*!
 * @file Car.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#ifndef _CAR_H
#define _CAR_H

#include "Motor.h"

namespace CAR {

/// @brief motor ID
  enum MotorId
  {
    rightMotor,
    leftMotor,
    bothMotors
  };

/// @brief class Car, with two motors
class Car 
{
//""""""""""""""""""""""""private object members
private:
    MOTOR::Motor MD;           ///< right motor object
    MOTOR::Motor ME;           ///< left motor object


public:

    //"""""""""""""""""""""""" constructor declaration

    Car();



    //""""""""""""""""""""""""public move member functions
public:
    /// @brief move car forward
    void moveForward();

    /// @brief move car backward
    void moveBackward();

    /// @brief stop car
    void stopMove();

    /// @brief turn car left and stop
    void turnLeft();

    /// @brief turn car right and stop
    void turnRight();



    //"""""""""""""""""""""""" public motor configuration member functions
public:
    /// @brief set turn new turn speed
    /// @param newTurnSpeed new speed
    void setTurnSpeed(int newTurnSpeed);

    /// @brief reset turn speed to default
    void resetTurnSpeed();

    /// @brief get current turn speed
    /// @return current turn speed
    int getTurnSpeed();

    /// @brief set new turn interval
    /// @param newIntervalSpeed new speed
    void setTurnInterval(int newInterval);

    /// @brief reset interval to default
    void resetTurnInterval();

    /// @brief get current interval
    /// @return current interval
    const int getTurnInterval();

    /// @brief set new motor speed
    /// @param motorID 'rightMotor','leftMotor' or 'bothMotors'
    /// @param newSpeed new speed
    void setMotorSpeed(int motorID, int newSpeed);

    /// @brief set new motor speed
    /// @param newSpeed new speed
    void setMotorSpeed(int newSpeed);

    /// @brief reset motor speed to default
    /// @param motorID 'rightMotor','leftMotor' or 'bothMotors'
    void resetMotorSpeed(int motorID = bothMotors);

    /// @brief get current motor speed
    /// @param motorID 'rightMotor','leftMotor' or 'bothMotors'
    /// @return current motor speed
    const int getMotorSpeed(int motorID = bothMotors);


    //""""""""""""""""""""""""private data members
private:
    /*************************************************
     * Adjust HERE the speed of the motors, according to 
     * the hardware, so as to keep the car in balance
    **************************************************/
    const int m_leftMotorSpeed{117};                  ///< left Motor speed
    const int m_rightMotorSpeed{120};                 ///< right Motor speed   
    const int m_defaultTurnSpeed{150};                ///< default turn speed
    const int m_defaultTurnInterval{500};             ///< default turn interval
    int m_currentTurnSpeed{m_defaultTurnSpeed};       ///< current turn speed
    int m_currentTurnInterval{m_defaultTurnInterval}; ///< current turn interval


};

}


#endif  //_CAR_H