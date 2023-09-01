#ifndef _MOTOR_H
#define _MOTOR_H

#include "Arduino.h"

class Motor {
  private:
    const int m_defaultSpeed{130};
    int m_actualMotorSpeed{m_defaultSpeed};
    int m_in1Pin{};
    int m_in2Pin{};
    int m_inpwmPin{};
    

   public:
    Motor(){};
    Motor(int in1,int in2, int inpwm);
    void forward(int speed);
    void backward(int speed);
    void forward();
    void backward();
    void off();
    void setMotorSpeed(int newSpeed);
    void resetMotorSpeed();
    int getMotorSpeed();

    
  
};

#endif
