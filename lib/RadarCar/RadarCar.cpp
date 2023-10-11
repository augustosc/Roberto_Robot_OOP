#include "RadarCar.h"
#include "UltraGpio.h"
#include "ServoGpio.h"
#include "MotorGpio.h"

/**
 *Do not use BT debug in RadarCar because of Servo library conflicts.
 Use ONLY Serial monitor debuf
*/
// #define _DEBUG


namespace RADARCAR
{

  //"""""""""""""""""""""""" constructor

  RadarCar::RadarCar(DFPLAYER::Dfplayer *DFP)
      : MD{MotorGpio::mDpin1, MotorGpio::mDpin2, MotorGpio::mDhab}, ME{MotorGpio::mEpin1, MotorGpio::mEpin2, MotorGpio::mEhab}, radar{UltraGpio::trigPin, UltraGpio::echoPin, ServoGpio::servoPin, ServoGpio::pulseMin, ServoGpio::pulseMax}, myDFP{DFP}
  {
    // Adjust motor speed
    MD.setMotorSpeed(m_rightMotorSpeed);
    ME.setMotorSpeed(m_leftMotorSpeed);
  }

  //"""""""""""""""""""""""" move methods

  void RadarCar::moveForward()
  {
    MD.forward();
    ME.forward();
  }

  //""""""""""""""""""""""""

  void RadarCar::moveBackward()
  {
    MD.backward();
    ME.backward();
  }

  //""""""""""""""""""""""""

  void RadarCar::stopMove()
  {
    MD.off();
    ME.off();
  }

  //""""""""""""""""""""""""

  void RadarCar::turnLeft()
  {
    this->stopMove();
    delay(500);
    MD.forward(m_currentTurnSpeed);
    ME.backward(m_currentTurnSpeed);
    delay(m_currentTurnInterval);
    this->stopMove();
  }

  //""""""""""""""""""""""""

  void RadarCar::turnRight()
  {
    this->stopMove();
    delay(500);
    MD.backward(m_currentTurnSpeed);
    ME.forward(m_currentTurnSpeed);
    delay(m_currentTurnInterval);
    this->stopMove();
  }

  //"""""""""""""""""""""""" map methods

  void RadarCar::radarAttach()
  {
    radar.attach();
  }

  //""""""""""""""""""""""""

  void RadarCar::radarDetach()
  {
    radar.detach();
  }

  //""""""""""""""""""""""""

  void RadarCar::lookAhead()
  {
    radar.lookAhead();
  }

  //""""""""""""""""""""""""

  void RadarCar::mapAhead()
  {
    obstacle.isClose = false;

    obstacle.distance[head] = radar.getDistanceAhead(0);

    if (obstacle.distance[head] < m_minObstacleDistance)
    {
      {
        stopMove();
        delay(100);
        moveBackward();
        delay(500);
        stopMove();
      }

      m_countStops++;
      obstacle.isClose = true;
    }

    checkMaxStops();

    checkStopMsgOnPause();
  }

  //""""""""""""""""""""""""

  void RadarCar::mapFront()
  {
    obstacle.isClose = false;

    obstacle.distance[diagRight] = radar.getDistanceDiagRight(100);

    if (obstacle.distance[diagRight] < m_minObstacleDistance)
    {
      stopMove();

      m_countStops++;
      obstacle.isClose = true;

      lookAhead();
      delay(150);

      checkMaxStops();

      return;
    }

    obstacle.distance[diagLeft] = radar.getDistanceDiagLeft(250);

    if (obstacle.distance[diagLeft] < m_minObstacleDistance)
    {
      stopMove();

      m_countStops++;
      obstacle.isClose = true;

      lookAhead();
      delay(150);

      checkMaxStops();
      return;
    }

    obstacle.distance[head] = radar.getDistanceAhead(100);

    if (obstacle.distance[head] < m_minObstacleDistance)
    {
      {
        stopMove();
        delay(100);
        moveBackward();
        delay(500);
        stopMove();
      }

      m_countStops++;
      obstacle.isClose = true;

      checkMaxStops();
    }
  }

  //""""""""""""""""""""""""

  void RadarCar::mapSide()
  {
    obstacle.distance[diagRight] = radar.getDistanceDiagRight(200);
    obstacle.distance[right] = radar.getDistanceRight(300);
    obstacle.distance[diagLeft] = radar.getDistanceDiagLeft(500);
    obstacle.distance[left] = radar.getDistanceLeft(300);
    this->lookAhead();
  }

  //""""""""""""""""""""""""

  bool RadarCar::shouldTurnRight()
  {
    this->mapSide();

    if (obstacle.distance[diagRight] < obstacle.distance[right])
    {
      obstacle.distance[right] = obstacle.distance[diagRight];
    }

    if (obstacle.distance[diagLeft] < obstacle.distance[left])
    {
      obstacle.distance[left] = obstacle.distance[diagLeft];
    }

    return (obstacle.distance[right] >= obstacle.distance[left]);
  }

  //""""""""""""""""""""""""

  struct obstacleInfo *RadarCar::getObstacleInfo()
  {
    return &obstacle;
  }

  //"""""""""""""""""""""""" turn methods

  void RadarCar::setTurnSpeed(int newTurnSpeed)
  {
    m_currentTurnSpeed = newTurnSpeed;
  }

  //""""""""""""""""""""""""

  void RadarCar::resetTurnSpeed()
  {
    m_currentTurnSpeed = m_defaultTurnSpeed;
  }

  //""""""""""""""""""""""""

  int RadarCar::getTurnSpeed()
  {
    return m_currentTurnSpeed;
  }

  //""""""""""""""""""""""""

  void RadarCar::setTurnInterval(int newInterval)
  {
    m_currentTurnInterval = newInterval;
  }

  //""""""""""""""""""""""""

  void RadarCar::resetTurnInterval()
  {
    m_currentTurnInterval = m_defaultTurnInterval;
  }

  //""""""""""""""""""""""""

  int RadarCar::getTurnInterval()
  {
    return m_currentTurnInterval;
  }

  //"""""""""""""""""""""""" speed methods

  void RadarCar::setMotorSpeed(int motorID, int newSpeed)
  {
    switch (motorID)
    {
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

  //""""""""""""""""""""""""

  void RadarCar::setMotorSpeed(int newSpeed)
  {
    setMotorSpeed(bothMotors, newSpeed);
  }

  //""""""""""""""""""""""""

  void RadarCar::resetMotorSpeed(int motorID)
  {

    switch (motorID)
    {
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

  //""""""""""""""""""""""""

  int RadarCar::getMotorSpeed(int motorID)
  {
    switch (motorID)
    {

    case rightMotor:
      return MD.getMotorSpeed();
      break;

    case leftMotor:
      return ME.getMotorSpeed();
      break;

    case bothMotors:
      if (MD.getMotorSpeed() == ME.getMotorSpeed())
        return MD.getMotorSpeed();
      else
        return 130;
    }
    return 0;
  }

  //""""""""""""""""""""""""

  void RadarCar::speakStopMsg()
  {
    // if DFP paused, 'start DFP' before play stop message as advertisement message
    if (myDFP->m_isPaused)
    {
#ifdef _DEBUG
      Serial.print("m_isSpeakingMsgOnPause OFF, busyPin = ");
      Serial.print(myDFP->readBusyPin());
      Serial.print("\tDFP state = ");
      Serial.println(myDFP->readState());
#endif
      myDFP->dfp.start();
      delay(100);

      myDFP->m_isPaused = !myDFP->m_isPaused;

      m_isSpeakingMsgOnPause = true;

      m_timeStopMsgStarted = millis();
    }

    myDFP->playStopMsg();
  }

  void RadarCar::checkMaxStops()
  {
    if (m_countStops >= m_maxStops)
    {
#ifdef _DEBUG
      Serial.print("m_countStops: ");
      Serial.println(m_countStops);
#endif
      m_countStops = 0;

      speakStopMsg();
    }
  }

  void RadarCar::checkStopMsgOnPause()
  {
    // wait for the message time duration and 'pause DFP' again
    if (m_isSpeakingMsgOnPause)
    {
#ifdef _DEBUG
      Serial.print("m_isSpeakingMsgOnPause ON, busyPin = ");
      Serial.print(myDFP->readBusyPin());
      Serial.print("\tDFP state = ");
      Serial.println(myDFP->readState());
#endif

      if ((millis() - m_timeStopMsgStarted) > m_stopMsgDuration /*|| myDFP->readBusyPin()*/)
      {
#ifdef _DEBUG
        Serial.print("m_isSpeakingMsgOnPause OFF, busyPin = ");
        Serial.print(myDFP->readBusyPin());
        Serial.print("\tDFP state = ");
        Serial.println(myDFP->readState());
#endif

        myDFP->dfp.pause();
        delay(100);

        myDFP->m_isPaused = !myDFP->m_isPaused;

        m_isSpeakingMsgOnPause = false;

#ifdef _DEBUG
        Serial.print("isSpeakMsgOnPause OFF, busyPin = ");
        Serial.print(myDFP->readBusyPin());
        Serial.print("\tDFP state = ");
        Serial.println(myDFP->readState());
#endif
      }
    }
  }

} // namespace RADARCAR
