#ifndef _RADAR_H
#define _RADAR_H

 #include "Arduino.h"
#include <Servo.h>
#include "Ultrasonic.h"

class Radar {
private:
    Servo servo;
    Ultrasonic ultrasonic;
    int m_servoID{};
    const int m_servoPin{};
    const int m_pulseMin{};
    const int m_pulseMax{};
    const int m_servoDelay{300};


public:
    Radar(){};
    Radar(const int trigPin, const int echoPin
        , const int servoPin, const int pulseMin,const int pulseMax);

    float getDistanceAhead();
    float getDistanceRight();
    float getDistanceDiagRight();
    float getDistanceLeft();
    float getDistanceDiagLeft();
    int moveServo(int angle);
    void attach();
    bool isAttached();
    int getServoID();
};
#endif
