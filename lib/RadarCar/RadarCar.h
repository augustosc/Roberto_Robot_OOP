#ifndef _RADARCAR_H
#define _RADARCAR_H

#include <Arduino.h>
#include "Motor.h"
#include "Radar.h"
#include "Dfplayer.h"
#include "MyPins.h"


///@brief Contains obstacle distance info
struct obstacleInfo {
    bool isClose;   /*!< set if obstacle is closer */
    float dist[5];  /*!< contains measured distances from obstacle */
};

/// @brief radar position
enum radarPosition {right, diagRight, head, diagLeft, left};

/// @brief motor ID
enum motorId{rightMotor,leftMotor,bothMotors};


 /// @brief Car with two motors and a radar
class RadarCar {
  private:
    
    Motor MD;             ///< right motor object
    Motor ME;             ///< left motor object
    Radar radar;          ///< radar object
    Dfplayer* myDFP;

    struct obstacleInfo obstacle{}; ///< obstacle info

    const int m_defaultTurnSpeed   {150}; ///< defautl turn speed
    const int m_defaultTurnInterval{800}; ///< defautl turn interval
    const int m_minObstacleDistance{30};  ///< min obstacle distance
    const int headPosition         {90};  ///< servo ahead position

    const int maxStops {4};     ///< stops before message stop
    int countStops{};           //< count nuber of stops

    int m_actualTurnSpeed{m_defaultTurnSpeed}; ///< actual turn speed
    int m_actualTurnInterval{m_defaultTurnInterval}; ///< actual turn interval


   public:

  RadarCar( Dfplayer* DFP)
      :MD{mDpin1,mDpin2,mDhab}, ME{mEpin1,mEpin2,mEhab},radar{trigPin,echoPin,servoPin,pulseMin,pulseMax}, myDFP{DFP}
    {}


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

#endif  //_RADARCAR_H
