#ifndef _IR_CTRL_H
#define _IR_CTRL_H

#include "SoftwareSerial.h"
#include "IRremote.h"
/** IRremote uses Arduino Timer 2*/
#include "RadarCar.h"
#include "Dfplayer.h"
#include "Led.h"
#include "BT.h"

/// @brief manage Roberto IR remote control
class IR
{
private:
    IRrecv receptor;             ///< IR receptor object
    decode_results comando;      ///< results object
    RADARCAR::RadarCar *Roberto; ///< pointer to Roberto object
    DFPLAYER::Dfplayer *myDFP;   ///< pointer to DFP object
    LED::Led *ledCtrl;           ///< pointer to Led object
    SoftwareSerial *bt;          ///< pointer to BT object

private:
    // keys of IR KEYS/LAFVIN
    static const unsigned long _um = 0xFF6897;
    static const unsigned long _dois = 0xFF9867;
    static const unsigned long _tres = 0xFFB04F;
    static const unsigned long _quatro = 0xFF30CF;
    static const unsigned long _cinco = 0xFF18E7;
    static const unsigned long _seis = 0xFF7A85;
    static const unsigned long _sete = 0xFF10EF;
    static const unsigned long _oito = 0xFF38C7;
    static const unsigned long _nove = 0xFF5AA5;
    static const unsigned long _zero = 0xFF4AB5;
    static const unsigned long _asterisco = 0xFF42BD;
    static const unsigned long _velha = 0xFF52AD;
    static const unsigned long _ok = 0xFF02FD;
    static const unsigned long _frente = 0xFF629D;
    static const unsigned long _tras = 0xFFA857;
    static const unsigned long _direita = 0xFFC23D;
    static const unsigned long _esquerda = 0xFF22DD;
    static const unsigned long _dup = 0xFFFFFFFF;

private:
    unsigned long m_IRLastTimeInLoop{};     ///< last time in radio loop
    static const int m_IRLoopTimeout{3000}; ///< timeout to check busyPin in radio loop

public:
    IR(RADARCAR::RadarCar *Car, DFPLAYER::Dfplayer *DFP, LED::Led *led, SoftwareSerial *_bt);

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
};

#endif //_IR_CTRL_H