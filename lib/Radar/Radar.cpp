 #include "Radar.h"
 
    Radar::Radar(const int trigPin, const int echoPin
      , const int servoPin, const int pulseMin,const int pulseMax) 

      : ultrasonic{trigPin,echoPin}
      ,m_servoPin{servoPin},m_pulseMin{pulseMin},m_pulseMax{pulseMax}
    {
      // do not attach servo inside class constructor
      // attaching the servo inside the main script setup()
    }
    
    float Radar::getDistanceAhead(){
        servo.write(headPosition);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }

    float Radar::getDistanceRight(){
        servo.write(rightPosition);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }

    float Radar::getDistanceDiagRight(){
        servo.write(diagRightPosition);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }

    float Radar::getDistanceLeft(){
        servo.write(leftPosition);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }
    float Radar::getDistanceDiagLeft(){
        servo.write(diagLeftPosition);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }

    int Radar::moveServo(int angle){
      servo.write(angle);
      return servo.read();
    }

    void Radar::attach(){
      m_servoID = servo.attach(m_servoPin,m_pulseMin,m_pulseMax);
    }
    
    bool Radar::isAttached(){
      return servo.attached();
    }
    
    int Radar::getServoID(){
      return m_servoID;
    }
