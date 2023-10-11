#ifndef _RADAR_H
#define _RADAR_H

#include <Arduino.h>
#include <Servo.h>
/**
 * Servo library uses Arduino Timer1 and conflicts with SoftwareSerial library (bluetooth), that disable interrupts while transmitting data.
 */
#include "Ultrasonic.h"

namespace RADAR
{

    /// @brief Class Radar with a servo and an ultrasonic to find obstacles
    class Radar
    {
    private:
        Servo servo;           ///< servo object by composition
        ULTRASONIC::Ultrasonic ultrasonic; ///< ultrasonic object by composition

    private:
        int m_servoID{};        ///< servoID
        const int m_servoPin{}; ///< servo control pin
        const int m_pulseMin{}; ///< servo pulse min
        const int m_pulseMax{}; ///< servo pulse max

    private:
        const int m_servoDelay{300}; ///< servo default delay after move
        const struct Position_struct
        { ///< radar position
            const int right{1};
            const int diagRight{40};
            const int head{90};
            const int diagLeft{140};
            const int left{179};
        } m_Position;

    public:
        //Radar(){};
        //Radar(const uint8_t trigPin, const uint8_t echoPin, const int servoPin, const int pulseMin, const int pulseMax);

        /// @brief Radar constructor
        /// @param trigPin ultrasonic trigger pin
        /// @param echoPin ultrasonic echo pin
        /// @param servoPin pin to control the servo motor
        /// @param pulseMin pulse min to servo motor
        /// @param pulseMax pulse max to servo motor
        Radar(const uint8_t trigPin, const uint8_t echoPin, const int servoPin, const int pulseMin, const int pulseMax);

        /// @brief measure obstacle distance ahead
        /// @param _delay necessary delay to move radar to the new position
        /// @return head distance in cm
        float getDistanceAhead(int _delay);

        /// @brief measure obstacle distance at right
        /// @param _delay necessary delay to move radar to the new position
        /// @return right distance in cm
        float getDistanceRight(int _delay);

        /// @brief measure obstacle distance at diagonal right
        /// @param _delay necessary delay to move radar to the new position
        /// @return diagonal right distance in cm
        float getDistanceDiagRight(int _delay);

        /// @brief measure obstacle distance at left
        /// @param _delay necessary delay to move radar to the new position
        /// @return left distance in cm
        float getDistanceLeft(int _delay);

        /// @brief measure obstacle distance at diagonal left
        /// @param _delay necessary delay to move radar to the new position
        /// @return diagonal left distance in cm
        float getDistanceDiagLeft(int _delay);

        /// @brief move servo head to specified position
        /// @param angle servo position: from 0 to 180 degree
        /// @return
        int moveServo(int angle);

        /// @brief attach servo motor
        void attach();

        /// @brief detach servo motor
        void detach();

        /// @brief check if servo is attached
        /// @return true if attached
        bool isAttached();

        /// @brief get servo ID
        /// @return ID
        int getServoID();

        /// @brief position radar ahead
        void lookAhead();
    };

} // namespace RADAR

#endif //_RADAR_H
