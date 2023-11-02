/*!
 * @file RadarCar.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */

#include "RadarCar.h"
#include "UltraGpio.h"
#include "ServoGpio.h"
//#include "MotorGpio.h"
#include "DfpGpio.h"

/**
 *Do not use BT debug in RadarCar because of Servo library conflicts.
 Use ONLY Serial monitor debuf
*/
// #define _DEBUG


namespace RADARCAR
{

  //"""""""""""""""""""""""" constructor definition

  RadarCar::RadarCar()
      : radar{UltraGpio::trigPin, UltraGpio::echoPin, ServoGpio::servoPin, ServoGpio::pulseMin, ServoGpio::pulseMax}, myDFP{DfpGpio::dfpRxPin,DfpGpio::dfpTxPin,DfpGpio::busyPin}
  {
  }

  
  //"""""""""""""""""""""""" public radar member functions

  void RadarCar::radarAttach()
  {
    radar.attach();
  }

  //""""""""""""""""""""""""

  void RadarCar::radarDetach()
  {
    radar.detach();
  }




  //"""""""""""""""""""""""" self drive member functions

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

  }

  //""""""""""""""""""""""""

  void RadarCar::mapFront()
  {
    obstacle.isClose = false;

    obstacle.distance[diagRight] = radar.getDistanceDiagRight(150);

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

    obstacle.distance[diagLeft] = radar.getDistanceDiagLeft(300);

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

    obstacle.distance[head] = radar.getDistanceAhead(150);

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
    obstacle.distance[diagRight] = radar.getDistanceDiagRight(250);
    obstacle.distance[right] = radar.getDistanceRight(250);
    obstacle.distance[diagLeft] = radar.getDistanceDiagLeft(500);
    obstacle.distance[left] = radar.getDistanceLeft(250);
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

  const struct obstacleInfo *RadarCar::getObstacleInfo()
  {
    return &obstacle;
  }




  //""""""""""""""""""""""""public DFPlayer member functions

  void RadarCar::speakStopMsg()
  {
    // if DFP paused, 'start DFP' before play stop message as advertisement message
    if (myDFP.getIsPaused())
    {
#ifdef _DEBUG
      Serial.print("m_isSpeakingMsgOnPause OFF, busyPin = ");
      Serial.print(myDFP->readBusyPin());
      Serial.print("\tDFP state = ");
      Serial.println(myDFP->readState());
#endif
      myDFP.startMusic();
      delay(100);

      myDFP.setIsPaused(!myDFP.getIsPaused());

      // set speaking stop message on pause flag
      m_isSpeakingMsgOnPause = true;

      m_timeStopMsgStarted = millis();
    }

    myDFP.playStopMsg();
  }


  //""""""""""""""""""""""""

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


  //""""""""""""""""""""""""

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

        myDFP.pauseMusic();
        delay(100);

        myDFP.setIsPaused(!myDFP.getIsPaused());

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


  //""""""""""""""""""""""""public DFPlayer delegate functions

  void RadarCar::playRandomMusic() {
    myDFP.playRandomMusic();
  }

    void RadarCar::pauseMusic(){
      myDFP.pauseMusic();
    }

    void RadarCar::volumeDown(){
      myDFP.volumeDown();
    }

    void RadarCar::volumeUp(){
      myDFP.volumeUp();
    }

    void RadarCar::playPreviousMusic(){
      myDFP.playPreviousMusic();
    }

    void RadarCar::playNextMusic(){
      myDFP.playNextMusic();
    }

    void RadarCar::pauseStartMusic(){
      myDFP.pauseStartMusic();
    }

    void RadarCar::playPreviousMsg(){
      myDFP.playPreviousMsg();
    }

    void RadarCar::playNextMsg(){
      myDFP.playNextMsg();
    }

    void RadarCar::playMenu(){
      myDFP.playMenu();
    }

} // namespace RADARCAR
