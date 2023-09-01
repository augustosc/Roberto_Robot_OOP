#include "RadarCar.h"

 //---------------------------------------------- constructor
  RadarCar::RadarCar(const int mEpin1, const int mEpin2, const int mDpin1, const int mDpin2
    , const int mEhab, const int mDhab
    ,const int trigPin, const int echoPin
    , const int servoPin, const int pulseMin,const int pulseMax)
    :MD{mDpin1,mDpin2,mDhab}, ME{mEpin1,mEpin2,mEhab},radar{trigPin,echoPin,servoPin,pulseMin,pulseMax}
    {
    }

 //---------------------------------------------- methods

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
    radar.moveServo(90);
    delay(300);
  }

  void RadarCar::mapAhead(){
    obstacle.dist[head] = radar.getDistanceAhead();
    if (obstacle.dist[head] < m_minObstacleDistance){
        this->stopMove();
        obstacle.isClose = true;
    }
    else obstacle.isClose = false;
  }

    
  void RadarCar::mapFront(){
    obstacle.dist[diagRight] = radar.getDistanceDiagRight();
    obstacle.dist[diagLeft] = radar.getDistanceDiagLeft();
    obstacle.dist[head] = radar.getDistanceAhead();

    if (obstacle.dist[head] < m_minObstacleDistance){
        this->stopMove();
        obstacle.isClose = true;
    }
    else if (obstacle.dist[diagRight] < m_minObstacleDistance){
        this->stopMove();
        obstacle.isClose = true;
    }
    else if (obstacle.dist[diagLeft] < m_minObstacleDistance){
        this->stopMove();
        obstacle.isClose = true;
    }
    else obstacle.isClose = false;
  }
  
  
  void RadarCar::mapSide(){
    obstacle.dist[diagRight]  = radar.getDistanceDiagRight();
    obstacle.dist[right]      = radar.getDistanceRight();
    obstacle.dist[diagLeft] = radar.getDistanceDiagLeft();
    obstacle.dist[left]     = radar.getDistanceLeft();
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


  
  struct obstacleMap * RadarCar::getObstacleInfo(){
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

   //----------------------------------------------  newSpeedoc
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
