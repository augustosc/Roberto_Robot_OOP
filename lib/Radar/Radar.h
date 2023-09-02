#ifndef _RADAR_H
#define _RADAR_H

#include <Arduino.h>
#include <Servo.h>
#include "Ultrasonic.h"

/// @brief Class Radar with a servo and an ultrasonic to find obstacles
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

    /// @brief Radar constructor
    /// @param trigPin ultrasonic trigger pin
    /// @param echoPin ultrasonic echo pin
    /// @param servoPin pin to control the servo motor
    /// @param pulseMin pulse min to servo motor
    /// @param pulseMax pulse max to servo motor
    Radar(const int trigPin, const int echoPin
        , const int servoPin, const int pulseMin,const int pulseMax);

    /// @brief measure obstacle distance ahead
    /// @return head distance
    float getDistanceAhead();

    /// @brief measure obstacle distance at right
    /// @return right distance
    float getDistanceRight();

    /// @brief measure obstacle distance at diagonal right
    /// @return diagonal right distance
    float getDistanceDiagRight();

    /// @brief measure obstacle distance at left
    /// @return left distance
    float getDistanceLeft();

    /// @brief measure obstacle distance at diagonal left
    /// @return diagonal left distance
    float getDistanceDiagLeft();

    /// @brief move servo head to specified position
    /// @param angle servo position: from 0 to 180 degree
    /// @return 
    int moveServo(int angle);

    /// @brief attach servo motor
    void attach();

    /// @brief check if servo is attached
    /// @return true if attached
    bool isAttached();

    /// @brief get servo ID 
    /// @return ID
    int getServoID();
};
#endif
