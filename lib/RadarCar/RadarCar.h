#ifndef _RADARCAR_H
#define _RADARCAR_H

#include "Arduino.h"
#include "Motor.h"
#include "Radar.h"

struct obstacleMap {
    bool isClose;
    float dist[5];
};

enum radarPosition {right, diagRight, head, diagLeft, left};
enum motorId{rightMotor,leftMotor,bothMotors};

class RadarCar {
  private:
    const int m_defaultTurnSpeed{150};
    const int m_defaultTurnInterval{800};
    const int m_minObstacleDistance{30};
    Motor MD;
    Motor ME;
    Radar radar;
    struct obstacleMap obstacle{};
    int m_actualTurnSpeed{m_defaultTurnSpeed};
    int m_actualTurnInterval{m_defaultTurnInterval};

   public:
 //---------------------------------------------- constructor
    RadarCar(){};
    RadarCar(const int mEpin1, const int mEpin2, const int mDpin1, const int mDpin2
            , const int mEhab, const int mDhab
            ,const int trigPin, const int echoPin
            , const int servoPin, const int pulseMin,const int pulseMax);


//---------------------------------------------- methods
//---------------------------------------------- move
    void moveForward();         
    void moveBackward();
    void stopMove();
    void turnLeft();
    void turnRight();

//---------------------------------------------- map
    void radarAttach();
    void lookAhead();
    void mapAhead();
    void mapFront();
    void mapSide();
    bool shouldTurnRight();
    
    struct obstacleMap * getObstacleInfo();

//---------------------------------------------- veloc Giro
    void setTurnSpeed(int newTurnSpeed);
    void resetTurnSpeed();
    int getTurnSpeed();

//---------------------------------------------- tempo Giro
    void setTurnInterval(int newInterval);
    void resetTurnInterval();
    int getTurnInterval();

//---------------------------------------------- veloc Motor
    void setMotorSpeed(int motorID,int newSpeed);
    void resetMotorSpeed(int motorID);
    int getMotorSpeed(int motorID);


  
};

#endif
