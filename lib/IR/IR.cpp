/*!
 * @file IR.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#include <Arduino.h>
#include "IR.h"
#include "CarState.h"
#include "IrGpio.h"

#define _DEBUG
//#define _DEBUG_BT


//"""""""""""""""""""""""" constructor definition 

IR::IR(SelfCar *Car, LED::Led *led, SoftwareSerial *_bt)
    : receptor{IrGpio::irPin}, comando{}, Roberto{Car},  ledCtrl{led}, bt{_bt}
{
}

//"""""""""""""""""""""""" IR begin

void IR::begin()
{
  receptor.enableIRIn();
}



//"""""""""""""""""""""""" public member functions

void IR::checkIRCommand()
{
#ifdef _DEBUG
  // Serial.println("checkIRCommand()");
  // BT.println("checkIRCommand()");
#endif

  if (Roberto->getState() != CarState::onBtControl)
  {
    if (receptor.decode(&comando))
    {

      if (comando.value == _go // turn ON/OFF remote control
          || comando.value == _radio  // turn ON/OFF radio
          || comando.value == _previousMusic // previous music
          || comando.value == _nextMusic   // next music
          || comando.value == _pause  // pause/restart music
          || comando.value == _volumeDown     // volume down
          || comando.value == _volumeUp   // volume up
          || comando.value == _previousMsg   // previous gm msg
          || comando.value == _nextMsg   // next gm msg
          || comando.value == _menu   // menu
        ) 
      {
        execIRCommand();
      }

      receptor.resume();

      delay(10); // delay for resume

    }
    IRcommandLoop();
  }
}



//""""""""""""""""""""""""

void IR::execIRCommand()
{
  switch (comando.value)
  {

  case _go: // turn ON/OFF remote control mode

    if (Roberto->getState() == CarState::automatic)
    {
      Roberto->updateState(CarState::onIrControl);

#ifdef _DEBUG
      Serial.println("*: turn ON remote control");
#endif
#ifdef _DEBUG_BT
      bt->println("*: turn ON remote control");
#endif

      Roberto->stopMove();

      ledCtrl->on();
    }
    else
    {
      Roberto->updateState(CarState::automatic);

#ifdef _DEBUG
      Serial.println("*: turn OFF remote control");
#endif
#ifdef _DEBUG_BT
      bt->println("*: turn OFF remote control");
#endif

      ledCtrl->off();
    }

    break;

  case _radio: // turn radio ON/OFF
    Roberto->myDFP.setRadioON(!Roberto->myDFP.getRadioON());
    if (Roberto->myDFP.getRadioON())
    {
      Roberto->playRandomMusic();

#ifdef _DEBUG
      Serial.println("#: turn ON radio");
#endif
#ifdef _DEBUG_BT
      bt->println("#: turn ON radio");
#endif 

    }
    else
    {
      Roberto->pauseMusic();

#ifdef _DEBUG
      Serial.println("#: turn OFF radio");
#endif
#ifdef _DEBUG_BT
      bt->println("#: turn OFF radio");
#endif

    }
    break;


  case _volumeDown: // Volume down
      Roberto->volumeDown();

#ifdef _DEBUG
    Serial.print("1: Volume down = ");
    Serial.println(Roberto->myDFP.getCurrentVoulme());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "1: volume down = %d", Roberto->myDFP.m_currentVolume);
      bt->println(buf);
    }
#endif

    break;


  case _volumeUp: // Volume up
      Roberto->volumeUp();

#ifdef _DEBUG
    Serial.print("3: Volume up = ");
    Serial.println(Roberto->myDFP.getCurrentVoulme());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "3: volume up = %d", Roberto->myDFP.m_currentVolume);
      bt->println(buf);
    }
#endif

    break;


  case _previousMusic: // previous music
    Roberto->playPreviousMusic();
    Roberto->myDFP.setRadioON(1);

#ifdef _DEBUG
    Serial.print("4: previous music = ");
    Serial.println(Roberto->myDFP.getCurrentMusic());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "4: previous music = %d", Roberto->myDFP.m_currentMusic);
      bt->println(buf);
    }
#endif

    break;



  case _pause: // pause/start music
    Roberto->pauseStartMusic();

#ifdef _DEBUG
        Serial.println("p: pause music");
#endif

    break;


  case _nextMusic: // next music
    Roberto->playNextMusic();
    Roberto->myDFP.setRadioON(1);

#ifdef _DEBUG
    Serial.print("6: next music = ");
    Serial.println(Roberto->myDFP.getCurrentMusic());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "6: next music = %d", Roberto->myDFP.m_currentMusic);
      bt->println(buf);
    }
#endif

    break;


  case _previousMsg: // previous good morning message
    Roberto->playPreviousMsg();

#ifdef _DEBUG
    Serial.print("7: previous gm msg = ");
    Serial.println(Roberto->myDFP.getCurrentGoodMorningMsg());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "7: previous gm msg = %d", Roberto->myDFP.m_currentGoodMorningMsg);
      bt->println(buf);
    }
#endif

    break;


  case _menu: // IR remote control menu
    Roberto->playMenu();

#ifdef _DEBUG
    Serial.println("8: MENU");
#endif
#ifdef _DEBUG_BT
    bt->println("8: MENU");
#endif

    break;


  case _nextMsg: // next good morning message
  Roberto->playNextMsg();

#ifdef _DEBUG
    Serial.print("9: next gm msg = "); Serial.println(Roberto->myDFP.getCurrentGoodMorningMsg());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "9: next gm msg = %d", Roberto->myDFP.m_currentGoodMorningMsg);
      bt->println(buf);
    }
#endif

    break;

  case _stop: // stop Roberto
    Roberto->stopMove();

#ifdef _DEBUG
    Serial.println("ok: stop");
#endif
#ifdef _DEBUG_BT
    bt->println("ok: stop");
#endif

    break;


  case _forward: // move Roberto forward
    Roberto->moveForward();

#ifdef _DEBUG
    Serial.println("^: forward");
#endif
#ifdef _DEBUG_BT
    bt->println("^: forward");
#endif

    break;


  case _backward: // move Roberto backward
    Roberto->moveBackward();

#ifdef _DEBUG
    Serial.println("v: backward");
#endif
#ifdef _DEBUG_BT
    bt->println("v: backward");
#endif

    break;


  case _turnRight: // turn Roberto right and stop
    Roberto->turnRight();
    Roberto->stopMove();

#ifdef _DEBUG
    Serial.println("-> turn right");
#endif
#ifdef _DEBUG_BT
    bt->println("-> turn right");
#endif

    break;

  case _turnLeft: // turn Roberto left and stop
    Roberto->turnLeft();
    Roberto->stopMove();

#ifdef _DEBUG
    Serial.println("<- turn left");
#endif
#ifdef _DEBUG_BT
    bt->println("<- turn left");
#endif

    break;


  case _dup:
    break;

  default: // ignore other comands

#ifdef _DEBUG
    Serial.print("other: 0x");
    Serial.println(comando.value, HEX);
#endif
#ifdef _DEBUG_BT
    bt->print("other: 0x");
    bt->println(comando.value, HEX);
#endif

    break;
  }
}




//"""""""""""""""""""""""" loop methods

void IR::IRcommandLoop()
{
  while (Roberto->getState() == CarState::onIrControl)
  {
    if (receptor.decode(&comando))
    {
      if (comando.value != _dup)
        execIRCommand();
      receptor.resume();
    }
    IRradioInLoop();

    /*****************/
    delay(100); // break loop
    /*****************/
  }
}

//""""""""""""""""""""""""

void IR::IRradioInLoop()
{
#ifdef _DEBUG
  //Serial.println("radioInLoop ()");
#endif
// #ifdef _DEBUG_BT
//   bt->println("radioEmLoop ()");
// #endif

  // check busyPin each 3s and,if that's the case, change music
  // busypin == LOW when playing
  if (Roberto->myDFP.getRadioON() && !Roberto->myDFP.getIsPaused() && millis() - m_IRLastTimeInLoop > m_IRLoopTimeout)
  {

#ifdef _DEBUG
    Serial.print("radio loop: busy pin = ");
    Serial.println(Roberto->myDFP.readBusyPin());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "radio loop: busy pin = %d", Roberto->myDFP.readBusyPin());
      // detach servo to eliminate conflict during BT transmit
      Roberto->radarDetach();
      bt->println(buf);
      Roberto->radarAttach();

    }
#endif

    if (Roberto->myDFP.readBusyPin())
    {
      comando.value = _nextMusic;
      execIRCommand();
    }
    m_IRLastTimeInLoop = millis();
  }
}
