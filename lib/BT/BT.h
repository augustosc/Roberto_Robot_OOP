/*!
 * @file BT.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#ifndef _BT_H
#define _BT_H

/**
 * SoftwareSerial disables interrupts while transmitting data, so it conflicts with Servo library.
 */
#include "SoftwareSerial.h"
#include "SelfCar.h"
#include "Led.h"


//""""""""""""""""""""""""class

/// @brief class to manage Roberto's BT remote control
class BT
{

//""""""""""""""""""""""""private object aggregation
private:
    SelfCar * Roberto;
    LED::Led *ledCtrl;           ///< pointer Led object


//""""""""""""""""""""""""public object aggregation
public:
    SoftwareSerial *bt; ///< Bluetooth object



//""""""""""""""""""""""""constructor declaration

    /// @brief constructor BT object
    /// @param Car pointer to self car object (Roberto)
    /// @param led pointer to Led object
    /// @param _bt pointer to Bluetooth object
    BT(SelfCar *Car, LED::Led *led, SoftwareSerial *_bt);



//""""""""""""""""""""""""public member functions

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



//""""""""""""""""""""""""private data members
private:
    //  Bluetooth keys
    static const char _forward = 'f';
    static const char _backward = 'b';
    static const char _turnRight = 'r';
    static const char _turnLeft = 'l';
    static const char _stop = 'x';
    static const char _go = '*';
    static const char _bt = 't';
    static const char _volumeDown = 'v';
    static const char _volumeUp = 'V';
    static const char _radio = '#';
    static const char _previousMusic = 'm';
    static const char _nextMusic = 'M';
    static const char _pause = 'p';
    static const char _previousMsg = 'g';
    static const char _nextMsg = 'G';
    static const char _menu = 'o';
    static const char _velDown = 'w';
    static const char _velUp = 'W';

private:
    char m_BTcommand{};                     ///< BT received command
    unsigned long m_BTLastTimeInLoop{};     ///< last time in radio loop
    static const int m_BTLoopTimeout{3000}; ///< timeout to check busyPin in radio loop
    int m_mSpeed{};                         ///< local motor speed

};

#endif //_BT_H