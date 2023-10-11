#include <Arduino.h>
#include "BT.h"
#include "CarState.h"

#define _DEBUG

/**
 * Isn't possible BT.cpp bluetooth debug, because SoftwreSerial library, that dives bluetooth transmit, disable interrupts and conflict with servo library.
 So, use only Serial monitor _DEBUG.
*/
//#define _DEBUG_BT


//"""""""""""""""""""""""" constructor

BT::BT(RADARCAR::RadarCar *Car, DFPLAYER::Dfplayer *dfp, LED::Led *led, SoftwareSerial *_bt)
    : Roberto{Car}, myDFP{dfp}, ledCtrl{led}, bt{_bt}
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
        if (robertoState != CarState::bluetooth)
        {
            Roberto->stopMove();
            robertoState = CarState::bluetooth;
            ledCtrl->on();
        }
#ifdef _DEBUG
        Serial.println("t: turn ON BT remote control");
#endif
#ifdef _DEBUG_BT
        bt->println("t: turn ON BT remote control");
#endif

        break;

    case _go: // active automatic mode
        if (robertoState != CarState::automatic)
        {
            robertoState = CarState::automatic;
            ledCtrl->off();
        }

#ifdef _DEBUG
        Serial.println("*: turn OFF BT remote control");
#endif
#ifdef _DEBUG_BT
        bt->println("*: turn OFF BT remote control");
#endif

        break;

    case _fwd: // move Roberto forward
#ifdef _DEBUG
        Serial.println("f: forward");

#endif
#ifdef _DEBUG_BT
        bt->println("f: forward");
#endif

        Roberto->moveForward();
        break;

    case _bwd: // move Roberto backward
#ifdef _DEBUG
        Serial.println("b: backward");
#endif
#ifdef _DEBUG_BT
        bt->println("b: backward");
#endif

        Roberto->moveBackward();
        break;

    case _right: // turn Roberto right
#ifdef _DEBUG
        Serial.println("r: turn right");
#endif
#ifdef _DEBUG_BT
        bt->println("r: turn right");
#endif

        Roberto->turnRight();
        Roberto->stopMove();
        break;

    case _left: // turn Roberto left
#ifdef _DEBUG
        Serial.println("l: turn left");
#endif
#ifdef _DEBUG_BT
        bt->println("l: turn left");
#endif

        Roberto->turnLeft();
        Roberto->stopMove();
        break;

    case _stop: // stop Roberto
#ifdef _DEBUG
        Serial.println("x: stop");
#endif
#ifdef _DEBUG_BT
        bt->println("x: stop");
#endif

        Roberto->stopMove();
        break;

    case _radio: // turn ON/OFF radio mode

        myDFP->m_currentMusic = random(1, myDFP->m_nMp3Files + 1);
        myDFP->m_radioON = !myDFP->m_radioON;

        if (myDFP->m_radioON)
        {
            myDFP->dfp.playMp3Folder(myDFP->m_currentMusic);

#ifdef _DEBUG
        Serial.print("#: radio ON, music = ");
        Serial.println(myDFP->m_currentMusic);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"#: radio ON, music = %d",myDFP->m_currentMusic);
        bt->println(buf);
        }
#endif
        }
        else
        {

#ifdef _DEBUG
        Serial.println("#: radio OFF");

#endif
#ifdef _DEBUG_BT
        bt->println("#: radio OFF");
#endif

            myDFP->dfp.pause();
        }
        break;

    case _volMinus: // volume down

        if (myDFP->m_currentVolume > 5)
        {
            myDFP->m_currentVolume--;
            myDFP->dfp.volumeDown();
        }

#ifdef _DEBUG
        Serial.print("v: Volume down = ");
        Serial.println(myDFP->m_currentVolume);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"v: Volume down = %d",myDFP->m_currentVolume);
        bt->println(buf);
        }
#endif

        break;

    case _volPlus: // volume up

        if (myDFP->m_currentVolume < 30)
        {
            myDFP->m_currentVolume++;
            myDFP->dfp.volumeUp();
        }
#ifdef _DEBUG
        Serial.print("V: Volume up = ");
        Serial.println(myDFP->m_currentVolume);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"V: Volume up = %d",myDFP->m_currentVolume);
        bt->println(buf);
        }
#endif
        break;

    case _musMinus: // play previous music
        if (myDFP->m_currentMusic > 1)
        {
            myDFP->m_currentMusic--;
        }
        else
        {
            myDFP->m_currentMusic = myDFP->m_nMp3Files;
        }
        myDFP->dfp.playMp3Folder(myDFP->m_currentMusic);
        myDFP->m_radioON = 1;

#ifdef _DEBUG
        Serial.print("m: previous music = ");
        Serial.println(myDFP->m_currentMusic);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"m: previous music = %d",myDFP->m_currentMusic);
        bt->println(buf);
        }
#endif

        break;

    case _musPlus: // play next music
        if (myDFP->m_currentMusic < myDFP->m_nMp3Files)
        {
            myDFP->m_currentMusic++;
        }
        else
        {
            myDFP->m_currentMusic = 1;
        }
        myDFP->dfp.playMp3Folder(myDFP->m_currentMusic);
        myDFP->m_radioON = 1;

#ifdef _DEBUG
        Serial.print("'M: next music = ");
        Serial.println(myDFP->m_currentMusic);

#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"M: next music = %d",myDFP->m_currentMusic);
        bt->println(buf);
        }
#endif

        break;

    case _pause: // pause/start music
#ifdef _DEBUG
        Serial.println("p: pause music");
#endif
#ifdef _DEBUG_BT
       bt->println("p: pause music");
#endif

        myDFP->m_isPaused = !myDFP->m_isPaused;
        if (myDFP->m_isPaused)
        {
            myDFP->dfp.pause();
        }
        else
        {
            myDFP->dfp.start();
            delay(150);
        }
        myDFP->m_radioON = 1;
        break;

    case _msgMinus: // previous good morning message

        if (myDFP->m_goodMorningMsg > 1)
            myDFP->m_goodMorningMsg--;
        else
            myDFP->m_goodMorningMsg = myDFP->m_nGoodMorningMsgFiles;
        myDFP->dfp.playFolder(1, myDFP->m_goodMorningMsg);

#ifdef _DEBUG
        Serial.print("g: previous gm msg = ");
        Serial.println(myDFP->m_goodMorningMsg);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"g: previous gm msg = %d",myDFP->m_goodMorningMsg);
        bt->println(buf);
        }
#endif
        break;

    case _msgPlus: // next good morning message

        if (myDFP->m_goodMorningMsg < myDFP->m_nGoodMorningMsgFiles)
            myDFP->m_goodMorningMsg++;
        else
            myDFP->m_goodMorningMsg = 1;
        myDFP->dfp.playFolder(1, myDFP->m_goodMorningMsg);

#ifdef _DEBUG
        Serial.print("G: next gm msg = ");
        Serial.println(myDFP->m_goodMorningMsg);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"G: next gm msg = %d",myDFP->m_goodMorningMsg);
        bt->println(buf);
        }
#endif

        break;

    case _menu: // IR remote control menu
#ifdef _DEBUG
        Serial.println("o: MENU");
#endif
#ifdef _DEBUG_BT
        bt->println("o: MENU");
#endif
        myDFP->dfp.playFolder(4, 1);
        break;

    case _velMinus: // motor speed down
        m_mSpeed = Roberto->getMotorSpeed();
        if (m_mSpeed > 110)
            Roberto->setMotorSpeed(m_mSpeed - 10);

#ifdef _DEBUG
        Serial.print("S: Vel - = ");
        Serial.println(m_mSpeed-10);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"S: Vel - = %d",m_mSpeed-10);
        bt->println(buf);
        }
#endif
        break;

    case _velPlus: // motor speed up
        m_mSpeed = Roberto->getMotorSpeed();
        if (m_mSpeed < 200)
            Roberto->setMotorSpeed(m_mSpeed + 10);

#ifdef _DEBUG
        Serial.print("S: Vel + = ");
        Serial.println(m_mSpeed+10);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"S: Vel + = %d",m_mSpeed+10);
        bt->println(buf);
        }
#endif
        break;

    default: // ignore other commands
#ifdef _DEBUG
        Serial.print("other = ");
        Serial.println(m_BTcommand);
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"outro = %c",m_BTcommand);
        bt->println(buf);
        }
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
             || m_BTcommand == _musPlus  // next music
             || m_BTcommand == _musMinus // previous music
             || m_BTcommand == _pause    // pause/restart music
             || m_BTcommand == _msgPlus  // next gm msg
             || m_BTcommand == _msgMinus // previous gm msg
             || m_BTcommand == _velPlus  // motor speed down
             || m_BTcommand == _velMinus // motor speed up
             || m_BTcommand == _volMinus // volume down
             || m_BTcommand == _volPlus  // volume up
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

    while (robertoState == CarState::bluetooth)
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
    if (myDFP->m_radioON && !myDFP->m_isPaused && millis() - m_BTLastTimeInLoop > m_BTLoopTimeout)
    {
#ifdef _DEBUG
        Serial.print("BT loop radio, busy pin = ");
        Serial.println(myDFP->readBusyPin());
#endif
#ifdef _DEBUG_BT
        {
        char buf[20];
        sprintf(buf,"BT loop radio, busy pin = %d",myDFP->readBusyPin());
        // detach servo to eliminate conflict during BT transmit
        Roberto->radarDetach();
        bt->println(buf);
        Roberto->radarAttach();
        }
#endif
        if (myDFP->readBusyPin())
        {
            m_BTcommand = _musPlus;
            execBTcommand();
        }
        m_BTLastTimeInLoop = millis();
    }
}
