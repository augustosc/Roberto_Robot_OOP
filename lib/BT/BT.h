#ifndef _BT_H
#define _BT_H

#include "SoftwareSerial.h"
/**
 * SoftwareSerial disables interrupts while transmitting data, so it conflicts with Servo library.
 */
#include "RadarCar.h"
#include "Dfplayer.h"
#include "Led.h"

/// @brief manage Roberto's BT remote control
class BT
{
private:
    RADARCAR::RadarCar *Roberto; ///< ponter to Roberto object
    DFPLAYER::Dfplayer *myDFP;   ///< pointer DFP object
    LED::Led *ledCtrl;           ///< pointer Led object

private:
    //  Bluetooth keys
    static const char _fwd = 'f';
    static const char _bwd = 'b';
    static const char _right = 'r';
    static const char _left = 'l';
    static const char _stop = 'x';
    static const char _go = '*';
    static const char _bt = 't';
    static const char _volMinus = 'v';
    static const char _volPlus = 'V';
    static const char _radio = '#';
    static const char _musMinus = 'm';
    static const char _musPlus = 'M';
    static const char _pause = 'p';
    static const char _msgMinus = 'g';
    static const char _msgPlus = 'G';
    static const char _menu = 'o';
    static const char _velMinus = 'w';
    static const char _velPlus = 'W';

private:
    char m_BTcommand{};                     ///< BT received command
    unsigned long m_BTLastTimeInLoop{};     ///< last time in radio loop
    static const int m_BTLoopTimeout{3000}; ///< timeout to check busyPin in radio loop
    int m_mSpeed{};                         ///< local motor speed


public:
    SoftwareSerial *bt; ///< Bluetooth object

    BT(RADARCAR::RadarCar *Car, DFPLAYER::Dfplayer *dfp, LED::Led *led, SoftwareSerial *_bt);

    /// @brief init BT remote control
    /// @param baud serial baud rate
    void begin(long baud);

    /// @brief set BT as listening
    /// @return true if replace another
    void listen();

    /// @brief execute bluetooth remote control commands
    void execBTcommand();

    /// @brief check bluetooth commands arrives
    void checkBTcommand();

    /// @brief manage music in continuos mode
    void BTradioInLoop();

    /// @brief receive and run remote BT commands
    void BTcommandLoop();
};

#endif //_BT_H