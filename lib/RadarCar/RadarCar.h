#ifndef _RADARCAR_H
#define _RADARCAR_H

#include <Arduino.h>
#include "Car.h"
#include "Radar.h"
#include "Dfplayer.h"


namespace RADARCAR
{

  //""""""""""""""""""""""""enums

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

  
  //""""""""""""""""""""""""class

  /// @brief class RadarCar inherit Car, plus radar and a DFPlayer
  class RadarCar : public CAR::Car
  {

  //""""""""""""""""""""""""private object composition
  private:
    RADAR::Radar radar;        ///< radar object


  //""""""""""""""""""""""""public object composition
  public:
    DFPLAYER::Dfplayer myDFP;  ///< DFP object
  
    

  //""""""""""""""""""""""""constructor declaration
  public:
    /// @brief Constructor
    RadarCar();



    //""""""""""""""""""""""""public radar delegate functions

    /// @brief attach radar servo motor
    void radarAttach();

    /// @brief detach radar servo motor
    void radarDetach();



    //"""""""""""""""""""""""" public self drive member functions
    
    /// @brief point radar ahead
    void lookAhead();

    /// @brief map obstacle distance ahead
    void mapAhead();

    /// @brief map obstacle distances: ahead, diagonal left and diagonal right
    void mapFront();

    /// @brief map obstacle distances: left, diagonal left, right and diagonal right
    void mapSide();

    /// @brief check best side to turn the car
    /// @return true if right side
    bool shouldTurnRight();

    /// @brief return struct obstacleInfo
    /// @return pointer to obstacleInfo
    const struct obstacleInfo *getObstacleInfo();

    
    

    //""""""""""""""""""""""""public DFPlayer member functions

    /// @brief play stop message. If on puse set flag stop message on pause
    void speakStopMsg();

    /// @brief check max stop has been reached
    void checkMaxStops();

    /// @brief check timeout of stop message on pause
    void checkStopMsgOnPause();



    //""""""""""""""""""""""""public DFPlayer delegate functions

    /// @brief delegates playRandomMusic
    void playRandomMusic();

    /// @brief delegates pauseMusic
    void pauseMusic();

    /// @brief delegates volumeDown
    void volumeDown();

    /// @brief delegates volumeUp
    void volumeUp();

    /// @brief delegates playPreviousMusic
    void playPreviousMusic();

    /// @brief delegates playNextMusic
    void playNextMusic();

    /// @brief delegates pauseStartMusic
    void pauseStartMusic();

    /// @brief delegates playPreviousMsg
    void playPreviousMsg();

    /// @brief delegates playNextMsg
    void playNextMsg();

    /// @brief delegates playMenu
    void playMenu();




  //""""""""""""""""""""""""protected data members
  protected:
    struct obstacleInfo obstacle                      ///< obstacle info
    {
    }; 

    const int m_minObstacleDistance{30};              ///< min obstacle distance
    const int m_maxStops{3};                          ///< stops before message stop
    int m_countStops{};                               ///< count nuber of stops
    const unsigned long m_stopMsgDuration{3000};      ///< max stopMsg duration
    unsigned long m_timeStopMsgStarted{};             ///< time stopMsg started
    bool m_isSpeakingMsgOnPause{};                    ///< flags playing msg on dfp pause
    

  };

} // namespace RADARCAR
#endif //_RADARCAR_H
