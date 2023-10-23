#include <Arduino.h>
#include "BT.h"
#include "CarState.h"

/**
 * Isn't possible BT.cpp bluetooth debug, because SoftwreSerial library, that dives bluetooth transmit, disable interrupts and conflict with servo library.
 So, use only Serial monitor _DEBUG.
*/

//#define _DEBUG


//"""""""""""""""""""""""" constructor

BT::BT(SelfCar *Car, LED::Led *led, SoftwareSerial *_bt)
    :  Roberto{Car}, ledCtrl{led}, bt{_bt}
{
}

//"""""""""""""""""""""""" begin

void BT::begin(long baud)
{
    bt->begin(baud);
}

//"""""""""""""""""""""""" listen

void BT::listen()
{
    bt->listen();
}

//"""""""""""""""""""""""" comand methods

void BT::execBTcommand()
{

    switch (m_BTcommand)
    {

    case _bt: // active BT remote control mode
        if (Roberto->getState() != CarState::onBtControl)
        {
            Roberto->stopMove();
            Roberto->updateState(CarState::onBtControl);
            ledCtrl->on();
        }
#ifdef _DEBUG
        Serial.println("t: turn ON BT remote control");
#endif
    break;


    case _go: // active automatic mode
        if (Roberto->getState() != CarState::automatic)
        {
            Roberto->updateState(CarState::automatic);
            ledCtrl->off();
        }
#ifdef _DEBUG
        Serial.println("*: turn OFF BT remote control");
#endif
    break;


    case _forward: // move Roberto forward
        Roberto->moveForward();
#ifdef _DEBUG
        Serial.println("f: forward");
#endif
    break;


    case _backward: // move Roberto backward
        Roberto->moveBackward();
#ifdef _DEBUG
        Serial.println("b: backward");
#endif
    break;


    case _turnRight: // turn Roberto right
        Roberto->turnRight();
        Roberto->stopMove();
#ifdef _DEBUG
        Serial.println("r: turn right");
#endif
    break;


    case _turnLeft: // turn Roberto left
        Roberto->turnLeft();
        Roberto->stopMove();
#ifdef _DEBUG
        Serial.println("l: turn left");
#endif
    break;


    case _stop: // stop Roberto
        Roberto->stopMove();
#ifdef _DEBUG
        Serial.println("x: stop");
#endif
    break;


    case _radio: // turn ON/OFF radio mode
        Roberto->myDFP.setRadioON(!Roberto->myDFP.getRadioON());
        //Roberto->myDFP.m_radioON = !Roberto->myDFP.m_radioON;
        if (Roberto->myDFP.getRadioON())
        {
            Roberto->playRandomMusic();
#ifdef _DEBUG
        Serial.print("#: radio ON, music = ");
        Serial.println(Roberto->myDFP.m_currentMusic);
#endif
        }
        else
        {
            Roberto->pauseMusic();
#ifdef _DEBUG
        Serial.println("#: radio OFF");
#endif
        }
    break;


    case _volumeDown: // volume down
        Roberto->volumeDown();
#ifdef _DEBUG
        Serial.print("v: Volume down = ");
        Serial.println(Roberto->myDFP.m_currentVolume);
#endif
    break;


    case _volumeUp: // volume up
        Roberto->volumeUp();

#ifdef _DEBUG
        Serial.print("V: Volume up = ");
        Serial.println(Roberto->myDFP.m_currentVolume);
#endif
    break;


    case _previousMusic: // play previous music
        Roberto->playPreviousMusic();
        Roberto->myDFP.setRadioON(1);
#ifdef _DEBUG
        Serial.print("m: previous music = ");
        Serial.println(Roberto->myDFP.m_currentMusic);
#endif
    break;


    case _nextMusic: // play next music
        Roberto->playNextMusic();
        Roberto->myDFP.setRadioON(1);
#ifdef _DEBUG
        Serial.print("'M: next music = ");
        Serial.println(Roberto->myDFP.m_currentMusic);
#endif
    break;


    case _pause: // pause/start music
        Roberto->pauseStartMusic();
#ifdef _DEBUG
        Serial.println("p: pause music");
#endif
    break;


    case _previousMsg: // previous good morning message
        Roberto->playPreviousMsg();
#ifdef _DEBUG
        Serial.print("g: previous gm msg = ");
        Serial.println(Roberto->myDFP.m_currentGoodMorningMsg);
#endif
    break;


    case _nextMsg: // next good morning message
        Roberto->playNextMsg();
#ifdef _DEBUG
        Serial.print("G: next gm msg = ");
        Serial.println(Roberto->myDFP.m_currentGoodMorningMsg);
#endif
    break;


    case _menu: // IR remote control menu
        Roberto->playMenu();
#ifdef _DEBUG
        Serial.println("o: MENU");
#endif
    break;


    case _velDown: // motor speed down
        m_mSpeed = Roberto->getMotorSpeed();
        if (m_mSpeed > 110)
            Roberto->setMotorSpeed(m_mSpeed - 10);
#ifdef _DEBUG
        Serial.print("S: Vel - = ");
        Serial.println(m_mSpeed-10);
#endif
    break;


    case _velUp: // motor speed up
        m_mSpeed = Roberto->getMotorSpeed();
        if (m_mSpeed < 200)
            Roberto->setMotorSpeed(m_mSpeed + 10);
#ifdef _DEBUG
        Serial.print("S: Vel + = ");
        Serial.println(m_mSpeed+10);
#endif
    break;


    default: // ignore other commands
#ifdef _DEBUG
        Serial.print("other = ");
        Serial.println(m_BTcommand);
#endif
    break;
    }
}

//""""""""""""""""""""""""

void BT::checkBTcommand()
{
    bt->listen();

    if (bt->available())
    {
        m_BTcommand = bt->read();
        if (m_BTcommand == _bt           // BT remote control
             || m_BTcommand == _radio    // radio ON/OFF
             || m_BTcommand == _nextMusic  // next music
             || m_BTcommand == _previousMusic // previous music
             || m_BTcommand == _pause    // pause/restart music
             || m_BTcommand == _nextMsg  // next gm msg
             || m_BTcommand == _previousMsg // previous gm msg
             || m_BTcommand == _velUp  // motor speed down
             || m_BTcommand == _velDown // motor speed up
             || m_BTcommand == _volumeDown // volume down
             || m_BTcommand == _volumeUp  // volume up
           )
        {
            execBTcommand();
        }
    }

    BTcommandLoop();
}

//"""""""""""""""""""""""" loop methods

void BT::BTcommandLoop()
{
    bt->listen();

    while (Roberto->getState() == CarState::onBtControl)
    {
        if (bt->available())
        {
            m_BTcommand = bt->read();

            if (m_BTcommand != _bt)
            {
                execBTcommand();
            }
        }
        BTradioInLoop();
    }
}

//""""""""""""""""""""""""

void BT::BTradioInLoop()
{
    // check busyPin each 3s and,if that's the case, change music
    // busypin == LOW when playing
    if (Roberto->myDFP.getRadioON() && !Roberto->myDFP.getIsPaused() && millis() - m_BTLastTimeInLoop > m_BTLoopTimeout)
    {
#ifdef _DEBUG
        Serial.print("BT loop radio, busy pin = ");
        Serial.println(Roberto->myDFP.readBusyPin());
#endif
        if (Roberto->myDFP.readBusyPin())
        {
            m_BTcommand = _nextMusic;
            execBTcommand();
        }
        m_BTLastTimeInLoop = millis();
    }
}
