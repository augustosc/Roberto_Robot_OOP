#ifndef _RADAR_H
#define _RADAR_H

#include <Arduino.h>
#include <Servo.h>
#include "Ultrasonic.h"

/// @brief Class Radar with a servo and an ultrasonic to find obstacles
class Radar {
private:
    Servo servo;                    ///< servo object
    Ultrasonic ultrasonic;          ///< ultrasonic object
    int m_servoID{};                ///< servoID
    const int m_servoPin{};         ///< servo control pin
    const int m_pulseMin{};         ///< servo pulse min
    const int m_pulseMax{};         ///< servo pulse max
   
    
public:
    const int m_servoDelay{300};    ///< servo default delay after move
    const int rightPosition     {1};
    const int diagRightPosition {40};
    const int headPosition      {90};
    const int diagLeftPosition  {140};
    const int leftPosition      {179};
    
    

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
    float getDistanceAhead(int _delay);

    /// @brief measure obstacle distance at right
    /// @return right distance
    float getDistanceRight(int _delay);

    /// @brief measure obstacle distance at diagonal right
    /// @return diagonal right distance
    float getDistanceDiagRight(int _delay);

    /// @brief measure obstacle distance at left
    /// @return left distance
    float getDistanceLeft(int _delay);

    /// @brief measure obstacle distance at diagonal left
    /// @return diagonal left distance
    float getDistanceDiagLeft(int _delay);

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
#endif  //_RADAR_H
