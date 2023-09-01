#include "Motor.h"

//--------------------------------------- construtor
  Motor::Motor(int in1Pin,int in2Pin, int inpwmPin)
  :m_in1Pin{in1Pin},m_in2Pin{in2Pin},m_inpwmPin{inpwmPin}
  {
    pinMode(m_in1Pin,OUTPUT);
    pinMode(m_in2Pin,OUTPUT);
    pinMode(m_inpwmPin,OUTPUT);
  }

//--------------------------------------- forward
  void Motor::forward(){
   analogWrite(m_inpwmPin,m_actualMotorSpeed);

   digitalWrite(m_in1Pin,HIGH);
   digitalWrite(m_in2Pin, LOW); 
  }
  
  void Motor::forward(int speed){             //overload used for Roberto.giraXXX methods
   analogWrite(m_inpwmPin,speed);

   digitalWrite(m_in1Pin,HIGH);
   digitalWrite(m_in2Pin, LOW); 
  }

//--------------------------------------- backward
  void Motor::backward(){
   analogWrite(m_inpwmPin,m_actualMotorSpeed);

   digitalWrite(m_in1Pin,LOW);
   digitalWrite(m_in2Pin, HIGH);
  }
  
  void Motor::backward(int speed){
   analogWrite(m_inpwmPin,speed);

   digitalWrite(m_in1Pin,LOW);
   digitalWrite(m_in2Pin, HIGH);
  }

//--------------------------------------- off
  void Motor::off(){
   digitalWrite(m_inpwmPin,LOW);

   digitalWrite(m_in1Pin,LOW);
   digitalWrite(m_in2Pin,LOW);
  }

//--------------------------------------- set and get velocM
  void Motor::setMotorSpeed(int newSpeed){
    m_actualMotorSpeed=newSpeed;
  }

  void Motor::resetMotorSpeed(){
    m_actualMotorSpeed=m_defaultSpeed;
  }
  
  int Motor::getMotorSpeed(){
    return m_actualMotorSpeed;
  }
