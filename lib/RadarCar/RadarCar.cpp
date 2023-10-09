#include "RadarCar.h"


  //---------------------------------------------- move
  void RadarCar::moveForward (){
     MD.forward();
     ME.forward();
  }

  void RadarCar::moveBackward () {
     MD.backward();
     ME.backward();
  }

  void RadarCar::stopMove (){
    MD.off();
    ME.off();
  }

  void RadarCar::turnLeft (){
    this->stopMove();
    delay(500);
    MD.forward(m_actualTurnSpeed);
    ME.backward(m_actualTurnSpeed);
    delay(m_actualTurnInterval);
    this->stopMove();
  }

  void RadarCar::turnRight (){
    this->stopMove();
    delay(500);
    MD.backward(m_actualTurnSpeed);
    ME.forward(m_actualTurnSpeed);
    delay(m_actualTurnInterval);
    this->stopMove();
  }

 //---------------------------------------------- map
  void RadarCar::radarAttach(){
    radar.attach();
  }
  
  void RadarCar::lookAhead(){
    radar.moveServo(radar.headPosition);
    delay(radar.m_servoDelay);
  }

  void RadarCar::mapAhead(){
    obstacle.dist[head] = radar.getDistanceAhead(0);
    if (obstacle.dist[head] < m_minObstacleDistance){
        this->stopMove();
        countStops++;
        obstacle.isClose = true;
    }
    else obstacle.isClose = false;
    if (countStops > maxStops) {countStops=0; myDFP->sendMsgStop();}
  }

    
  void RadarCar::mapFront()
  {
    obstacle.isClose = false;
    obstacle.dist[diagRight] = radar.getDistanceDiagRight(100);
    if (obstacle.dist[diagRight] < m_minObstacleDistance){
        this->stopMove();
        countStops++;
        obstacle.isClose = true;
        this->lookAhead();
        delay(150);
        return;
    }
  
    obstacle.dist[diagLeft] = radar.getDistanceDiagLeft(250);
    if (obstacle.dist[diagLeft] < m_minObstacleDistance){
        this->stopMove();
        countStops++;
        obstacle.isClose = true;
        this->lookAhead();
        delay(150);
        return;
    }

    obstacle.dist[head] = radar.getDistanceAhead(100);
    if (obstacle.dist[head] < m_minObstacleDistance){
        this->stopMove();
        countStops++;
        obstacle.isClose = true;
    }
    
  }
  
  
  void RadarCar::mapSide(){
    obstacle.dist[diagRight]  = radar.getDistanceDiagRight(200);
    obstacle.dist[right]      = radar.getDistanceRight(300);
    obstacle.dist[diagLeft] = radar.getDistanceDiagLeft(500);
    obstacle.dist[left]     = radar.getDistanceLeft(300);
    this->lookAhead();
  }
  
  bool RadarCar::shouldTurnRight(){
    this->mapSide();

    if (obstacle.dist[diagRight]  < obstacle.dist[right]){
        obstacle.dist[right] = obstacle.dist[diagRight];
    }

    if (obstacle.dist[diagLeft]  < obstacle.dist[left]){
        obstacle.dist[left] = obstacle.dist[diagLeft];
    }

    return (obstacle.dist[right] >= obstacle.dist[left]);
  }


  
  struct obstacleInfo * RadarCar::getObstacleInfo(){
    return &obstacle;
  }

  
   //---------------------------------------------- Giro
  void RadarCar::setTurnSpeed(int newTurnSpeed){
    m_actualTurnSpeed=newTurnSpeed;
  }

  void RadarCar::resetTurnSpeed(){
    m_actualTurnSpeed=m_defaultTurnSpeed;
  }
  
  int RadarCar::getTurnSpeed() {
    return m_actualTurnSpeed;
  }
  
  void RadarCar::setTurnInterval(int newInterval){
    m_actualTurnInterval=newInterval;
  }

  void RadarCar::resetTurnInterval(){
    m_actualTurnInterval=m_defaultTurnInterval;
  }
  
  int RadarCar::getTurnInterval() {
    return m_actualTurnInterval;
  }


  void RadarCar::setMotorSpeed(int motorID,int newSpeed){
    switch(motorID) {
      case rightMotor:
        MD.setMotorSpeed(newSpeed);
      break;
      
      case leftMotor:
        ME.setMotorSpeed(newSpeed);
      break;
      
      case bothMotors:
        MD.setMotorSpeed(newSpeed);
        ME.setMotorSpeed(newSpeed);
     
    }
  }
  void RadarCar::resetMotorSpeed(int motorID){
    
    switch(motorID) {
      case rightMotor:
        MD.resetMotorSpeed();
      break;
      
      case leftMotor:
        ME.resetMotorSpeed();
      break;
      
      case bothMotors:
        MD.resetMotorSpeed();
        ME.resetMotorSpeed();
     
    }
  }
  
  int RadarCar::getMotorSpeed(int motorID){
    switch(motorID) {
    
      case rightMotor:
        return MD.getMotorSpeed();
      break;
      
      case leftMotor:
        return ME.getMotorSpeed();
      break;
      
      case bothMotors:
       if (MD.getMotorSpeed() == ME.getMotorSpeed()) return MD.getMotorSpeed();
       else return 130;
     
    }
    return 0;
  }
