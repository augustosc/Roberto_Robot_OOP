#ifndef _RADARCAR_H
#define _RADARCAR_H

#include <Arduino.h>
#include "Motor.h"
#include "Radar.h"


///@brief Contains obstacle distance info
struct obstacleInfo {
    bool isClose;   /*!< set if obstacle is closer */
    float dist[5];  /*!< contains measured distances from obstacle */
};

enum radarPosition {right, diagRight, head, diagLeft, left};
enum motorId{rightMotor,leftMotor,bothMotors};

/**
 * @brief RadarCar class with two motors and a radar
*/
class RadarCar {
  private:
    const int m_defaultTurnSpeed{150};
    const int m_defaultTurnInterval{800};
    const int m_minObstacleDistance{30};
    Motor MD;
    Motor ME;
    Radar radar;
    struct obstacleInfo obstacle{};
    int m_actualTurnSpeed{m_defaultTurnSpeed};
    int m_actualTurnInterval{m_defaultTurnInterval};

   public:
    RadarCar(){};

    /// @brief RadarCar constructor
    /// @param mEpin1 left motor L298 pin1
    /// @param mEpin2 left motor L298 pin2
    /// @param mDpin1 right motor L298 pin1
    /// @param mDpin2 right motor L298 pin2
    /// @param mEhab  left motor L298D pwm pin
    /// @param mDhab  right motor L298D pwm pin
    /// @param trigPin ultrasonic trigger pin
    /// @param echoPin ultrasonic echo pin
    /// @param servoPin servo motor pin
    /// @param pulseMin servo motor pulse min
    /// @param pulseMax servo motor pulse max
    RadarCar(const int mEpin1, const int mEpin2, const int mDpin1, const int mDpin2
            , const int mEhab, const int mDhab
            ,const int trigPin, const int echoPin
            , const int servoPin, const int pulseMin,const int pulseMax);


    /// @brief move car forward
    void moveForward();   

    /// @brief move car backward
    void moveBackward();

    /// @brief stop car
    void stopMove();

    /// @brief turn car left
    void turnLeft();

    /// @brief turn car right
    void turnRight();

    /// @brief attach radar servo motor
    void radarAttach();

    /// @brief point radar ahead
    void lookAhead();

    /// @brief map obstacle distance ahead
    void mapAhead();

    /// @brief map obstacle distance ahead, diagonal left and diagonal right
    void mapFront();

    /// @brief map obstacle distance left, diagonal left, right and diagonal right
    void mapSide();

    /// @brief check free side to turn car
    /// @return true if right is free to turn
    bool shouldTurnRight();
    
    /// @brief return struct obstacleInfo
    /// @return pointer to obstacleInfo
    struct obstacleInfo * getObstacleInfo();

    /// @brief set turn new turn speed
    /// @param newTurnSpeed 
    void setTurnSpeed(int newTurnSpeed);

    /// @brief reset turn speed to default
    void resetTurnSpeed();

    /// @brief get actual turn speed
    /// @return actual turn speed
    int getTurnSpeed();

    /// @brief set new turn interval
    /// @param newIntervalSpeed 
    void setTurnInterval(int newInterval);

    /// @brief reset interval to default
    void resetTurnInterval();

    /// @brief get actual interval
    /// @return actual interval
    int getTurnInterval();

    /// @brief set new motor speed
    /// @param motorID 
    /// @param newSpeed 
    void setMotorSpeed(int motorID,int newSpeed);

    /// @brief reset motor speed to default
    /// @param motorID 
    void resetMotorSpeed(int motorID);

    /// @brief get actual motor speed
    /// @param motorID 
    /// @return actual motor speed
    int getMotorSpeed(int motorID);


  
};

#endif
