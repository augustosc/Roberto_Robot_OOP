#ifndef _DFPLAYER_H
#define _DFPLAYER_H

#include <Arduino.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

/// @brief Dfplayer class manage DFplayer Mini
class Dfplayer {
   
public:
    
    DFRobotDFPlayerMini dfp;    ///< dfp object
    SoftwareSerial dfpSerial;   ///< dfp software serial

public:
    const int m_busyPin{};  ///< DFP busy pin (LOW when busy)
    int musicaAtual {1};    ///< DFP music in play
    int volumeAtual {18};   ///< actual volume from 0 t0 30
    int msgAtual {};        ///< saves actual "bom dia" message
    int msgBomDia {1};      
    long nArqvMsgStop{};    ///< quantity of msgStops
    long nArqvMsgBomDia{};  ///< quantity of MsgBomDia
    long nArqvMp3{};        ///< quantity music files
    long nArqvMenu{};       ///< quantity menu files
    bool radioON {0};       ///< manage radio in continuos mode
    bool pauseRadio {0};

    Dfplayer (const uint8_t rxPin, const uint8_t txPin, const int busyPin)
    : dfp{}, dfpSerial{rxPin,txPin}, m_busyPin{busyPin}
    {}


    /// @brief init DFP
    void begin();
    
    /// @brief play Stop messages
    void sendMsgStop();

    /// @brief play Good Morning messages
    void sendGoodMorning();

    /// @brief set actual volume
    /// @param vol from 0 to 30
    void setVolume(int vol);



    



};


#endif  //_DFPLAYER_H