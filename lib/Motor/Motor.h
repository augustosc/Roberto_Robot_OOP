#ifndef _MOTOR_H
#define _MOTOR_H

#include "Arduino.h"

/// @brief Class to control DC motor by L298D driver
class Motor {
  private:
    const int m_defaultSpeed{130};
    int m_actualMotorSpeed{m_defaultSpeed};
    int m_in1Pin{};
    int m_in2Pin{};
    int m_inpwmPin{};
    

   public:
    Motor(){};

    /// @brief create motor object
    /// @param in1 pin1 to L298D
    /// @param in2 pin2 to L298D
    /// @param inpwm pin pwm to L298D
    Motor(int in1,int in2, int inpwm);

    /// @brief move motor forward at default speed
    void forward();

    /// @brief move motor forward at specified speed
    void forward(int speed);

    /// @brief move motor backward at default speed
    void backward();

    /// @brief move motor backward at specified speed
    void backward(int speed);

    /// @brief turn off motor
    void off();

    /// @brief set new speed to motor
    void setMotorSpeed(int newSpeed);

    /// @brief reset motor speed to default
    void resetMotorSpeed();

    /// @brief get motor speed
    /// @return actual motor speed
    int getMotorSpeed();

    
  
};

#endif
