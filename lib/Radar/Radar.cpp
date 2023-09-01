 #include "Radar.h"
 
    Radar::Radar(const int trigPin, const int echoPin
      , const int servoPin, const int pulseMin,const int pulseMax) 
      : ultrasonic{trigPin,echoPin}
      ,m_servoPin{servoPin},m_pulseMin{pulseMin},m_pulseMax{pulseMax}
    {
    }
    
    float Radar::getDistanceAhead(){
        servo.write(90);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }
    float Radar::getDistanceRight(){
        servo.write(1);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }
    float Radar::getDistanceDiagRight(){
        servo.write(40);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }
    float Radar::getDistanceLeft(){
        servo.write(179);
        delay(m_servoDelay);
        return ultrasonic.getDistance();
    }
    float Radar::getDistanceDiagLeft(){
        servo.write(140);
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
