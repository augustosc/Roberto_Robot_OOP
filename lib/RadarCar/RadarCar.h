#ifndef _RADARCAR_H
#define _RADARCAR_H

#include <Arduino.h>
#include "Motor.h"
#include "Radar.h"
#include "Dfplayer.h"


namespace RADARCAR
{

  ///@brief Contains obstacle distance info
  struct obstacleInfo
  {
    bool isClose;      /*!< set if obstacle is closer */
    float distance[5]; /*!< array contains measured distances from obstacle */
  };

  /// @brief radar position
  enum radarPosition
  {
    right,
    diagRight,
    head,
    diagLeft,
    left
  };

  /// @brief motor ID
  enum MotorId
  {
    rightMotor,
    leftMotor,
    bothMotors
  };

  /// @brief Car with two motors, a DFP and a radar
  class RadarCar
  {

  private:
    MOTOR::Motor MD;           ///< right motor object
    MOTOR::Motor ME;           ///< left motor object
    RADAR::Radar radar;        ///< radar object
    DFPLAYER::Dfplayer *myDFP; ///< DFP object
  
    struct obstacleInfo obstacle
    {
    }; ///< obstacle info

  private:
    
    /*************************************************
     * Adjust HERE the speed of the motors, according to 
     * the hardware, so as to keep the car in balance
    **************************************************/
    const int m_leftMotorSpeed{117};                  ///< left Motor speed
    const int m_rightMotorSpeed{120};                 ///< right Motor speed
    
    const int m_defaultTurnSpeed{150};                ///< defautl turn speed
    const int m_defaultTurnInterval{500};             ///< defautl turn interval
    int m_currentTurnSpeed{m_defaultTurnSpeed};       ///< current turn speed
    int m_currentTurnInterval{m_defaultTurnInterval}; ///< current turn interval
    const int m_minObstacleDistance{30};              ///< min obstacle distance
    const int m_maxStops{3};                          ///< stops before message stop
    int m_countStops{};                               ///< count nuber of stops
    const unsigned long m_stopMsgDuration{3000};      ///< max stopMsg duration
    unsigned long m_timeStopMsgStarted{};             ///< time stopMsg started
    bool m_isSpeakingMsgOnPause{};                    ///< flags playing msg on dfp pause


  public:

    /// @brief Car with 2 motors, a radar and Dfplayer mini
    /// @param DFP DFplayer object by aggregation
    RadarCar(DFPLAYER::Dfplayer *DFP);

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

    /// @brief detach radar servo motor
    void radarDetach();

    /// @brief point radar ahead
    void lookAhead();

    /// @brief map obstacle distance ahead
    void mapAhead();

    /// @brief map obstacle distance ahead, diagonal left and diagonal right
    void mapFront();

    /// @brief map obstacle distance left, diagonal left, right and diagonal right
    void mapSide();

    /// @brief check best side to turn the car
    /// @return true if right
    bool shouldTurnRight();

    /// @brief return struct obstacleInfo
    /// @return pointer to obstacleInfo
    struct obstacleInfo *getObstacleInfo();

    /// @brief set turn new turn speed
    /// @param newTurnSpeed new speed
    void setTurnSpeed(int newTurnSpeed);

    /// @brief reset turn speed to default
    void resetTurnSpeed();

    /// @brief get current turn speed
    /// @return current turn speed
    int getTurnSpeed();

    /// @brief set new turn interval
    /// @param newIntervalSpeed new speed
    void setTurnInterval(int newInterval);

    /// @brief reset interval to default
    void resetTurnInterval();

    /// @brief get current interval
    /// @return current interval
    int getTurnInterval();

    /// @brief set new motor speed
    /// @param motorID 'rightMotor','leftMotor' or 'bothMotors'
    /// @param newSpeed new speed
    void setMotorSpeed(int motorID, int newSpeed);

    /// @brief set new motor speed
    /// @param newSpeed new speed
    void setMotorSpeed(int newSpeed);

    /// @brief reset motor speed to default
    /// @param motorID 'rightMotor','leftMotor' or 'bothMotors'
    void resetMotorSpeed(int motorID = bothMotors);

    /// @brief get current motor speed
    /// @param motorID 'rightMotor','leftMotor' or 'bothMotors'
    /// @return current motor speed
    int getMotorSpeed(int motorID = bothMotors);

    /// @brief play stop message
    void speakStopMsg();

    /// @brief check max stop has been reached
    void checkMaxStops();

    /// @brief check msg stop on pause to pause music
    void checkStopMsgOnPause();
  };

} // namespace RADARCAR
#endif //_RADARCAR_H
