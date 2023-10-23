#ifndef _IR_CTRL_H
#define _IR_CTRL_H

#include "SoftwareSerial.h"
#include "IRremote.h"       /** IRremote uses Arduino Timer 2*/
#include "SelfCar.h"
#include "Led.h"
#include "BT.h"



//""""""""""""""""""""""""class

/// @brief class to manage Roberto IR remote control
class IR
{

//""""""""""""""""""""""""private object composition
private:
    IRrecv receptor;             ///< IR receptor object
    decode_results comando;      ///< results object


//""""""""""""""""""""""""private object aggregation
private:
    SelfCar *Roberto;
    LED::Led *ledCtrl;           ///< pointer to Led object
    SoftwareSerial *bt;          ///< pointer to BT object
    


//""""""""""""""""""""""""constructor declaration
public:
    /// @brief constructor IR object
    /// @param Car pointer to selfCar object (Roberto)
    /// @param led pointer to Led object
    /// @param _bt pointer to Bluetooth object
    IR(SelfCar *Car, LED::Led *led, SoftwareSerial *_bt);



//""""""""""""""""""""""""public member functions

    /// @brief init IR remote control
    void begin();

    /// @brief check IR remote control command
    void checkIRCommand();

    /// @brief execute IR remote control command
    void execIRCommand();

    /// @brief receive and run IR remote control commands
    void IRcommandLoop();

    /// @brief manage music in continuos mode
    void IRradioInLoop();



//""""""""""""""""""""""""keys code of IR KEYS/LAFVIN
private:
    static const unsigned long _volumeDown = 0xFF6897;
    static const unsigned long _dois = 0xFF9867;
    static const unsigned long _volumeUp = 0xFFB04F;
    static const unsigned long _previousMusic = 0xFF30CF;
    static const unsigned long _pause = 0xFF18E7;
    static const unsigned long _nextMusic = 0xFF7A85;
    static const unsigned long _previousMsg = 0xFF10EF;
    static const unsigned long _menu = 0xFF38C7;
    static const unsigned long _nextMsg = 0xFF5AA5;
    static const unsigned long _zero = 0xFF4AB5;
    static const unsigned long _go = 0xFF42BD;
    static const unsigned long _radio = 0xFF52AD;
    static const unsigned long _stop = 0xFF02FD;
    static const unsigned long _forward = 0xFF629D;
    static const unsigned long _backward = 0xFFA857;
    static const unsigned long _turnRight = 0xFFC23D;
    static const unsigned long _turnLeft = 0xFF22DD;
    static const unsigned long _dup = 0xFFFFFFFF;


//""""""""""""""""""""""""private data members
private:
    unsigned long m_IRLastTimeInLoop{};     ///< last time in radio loop
    static const int m_IRLoopTimeout{3000}; ///< timeout to check busyPin in radio loop

};

#endif //_IR_CTRL_H