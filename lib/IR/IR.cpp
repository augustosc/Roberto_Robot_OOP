#include <Arduino.h>
#include "IR.h"
#include "Dfplayer.h"
#include "CarState.h"
#include "IrGpio.h"

//#define _DEBUG
#define _DEBUG_BT


//"""""""""""""""""""""""" constructor
IR::IR(RADARCAR::RadarCar *Car, DFPLAYER::Dfplayer *DFP, LED::Led *led, SoftwareSerial *_bt)
    : receptor{IrGpio::irPin}, comando{}, Roberto{Car}, myDFP{DFP}, ledCtrl{led}, bt{_bt}
{
}

//"""""""""""""""""""""""" begin

void IR::begin()
{
  receptor.enableIRIn();
}

//"""""""""""""""""""""""" command methods

void IR::execIRCommand()
{
  switch (comando.value)
  {

  case _asterisco: // turn ON/OFF remote control mode

    if (robertoState == CarState::automatic)
    {
      robertoState = CarState::remoteControl;

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
      robertoState = CarState::automatic;

#ifdef _DEBUG
      Serial.println("*: turn OFF remote control");
#endif
#ifdef _DEBUG_BT
      bt->println("*: turn OFF remote control");
#endif

      ledCtrl->off();
    }

    break;

  case _velha: // turn ON/OFF radio
    myDFP->m_currentMusic = random(1, myDFP->m_nMp3Files + 1);

    myDFP->m_radioON = !myDFP->m_radioON;

    //Roberto->myDFP->m_radioON = 0;

    if (myDFP->m_radioON)
    {

#ifdef _DEBUG
      Serial.println("#: turn ON radio");
#endif
#ifdef _DEBUG_BT
      bt->println("#: turn ON radio");
#endif

      myDFP->dfp.playMp3Folder(myDFP->m_currentMusic);
    }
    else
    {

#ifdef _DEBUG
      Serial.println("#: turn OFF radio");
#endif
#ifdef _DEBUG_BT
      bt->println("#: turn OFF radio");
#endif

      myDFP->dfp.pause();
    }
    break;

  case _um: // Volume down

    if (myDFP->m_currentVolume > 5)
    {
      myDFP->m_currentVolume--;
      myDFP->dfp.volumeDown();
    }

#ifdef _DEBUG
    Serial.print("1: Volume down = ");
    Serial.println(myDFP->m_currentVolume);
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "1: volume down = %d", myDFP->m_currentVolume);
      bt->println(buf);
    }
#endif
    break;

  case _tres: // Volume up

    if (myDFP->m_currentVolume < 30)
    {
      myDFP->m_currentVolume++;
      myDFP->dfp.volumeUp();
    }

#ifdef _DEBUG
    Serial.print("3: Volume up = ");
    Serial.println(myDFP->m_currentVolume);
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "3: volume up = %d", myDFP->m_currentVolume);
      bt->println(buf);
    }
#endif

    break;

  case _quatro: // previous music

    (myDFP->m_currentMusic > 1) ? myDFP->m_currentMusic-- : myDFP->m_currentMusic = myDFP->m_nMp3Files;

#ifdef _DEBUG
    Serial.print("4: previous music = ");
    Serial.println(myDFP->m_currentMusic);
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "4: previous music = %d", myDFP->m_currentMusic);
      bt->println(buf);
    }
#endif

    myDFP->dfp.playMp3Folder(myDFP->m_currentMusic);

    myDFP->m_radioON = 1;
    break;

  case _cinco: // pause/start music

    myDFP->m_isPaused = !myDFP->m_isPaused;

    if (myDFP->m_isPaused)
    {

#ifdef _DEBUG
      Serial.println("5: pause music");
#endif
#ifdef _DEBUG_BT
      bt->println("5: pause music");
#endif

      myDFP->dfp.pause();
    }
    else
    {

#ifdef _DEBUG
      Serial.println("5: restart music");
#endif
#ifdef _DEBUG_BT
      bt->println("5: restart music");
#endif

      myDFP->dfp.start();
      delay(150);
    }
    myDFP->m_radioON = 1;
    break;

  case _seis: // next music
    (myDFP->m_currentMusic < myDFP->m_nMp3Files) ? myDFP->m_currentMusic++ : myDFP->m_currentMusic = 1;

#ifdef _DEBUG
    Serial.print("6: next music = ");
    Serial.println(myDFP->m_currentMusic);
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "6: next music = %d", myDFP->m_currentMusic);
      bt->println(buf);
    }
#endif

    myDFP->dfp.playMp3Folder(myDFP->m_currentMusic);

    myDFP->m_radioON = 1;
    break;

  case _sete: // previous good morning message

    (myDFP->m_goodMorningMsg > 1) ? myDFP->m_goodMorningMsg-- : myDFP->m_nGoodMorningMsgFiles;

#ifdef _DEBUG
    Serial.print("7: previous gm msg = ");
    Serial.println(myDFP->m_goodMorningMsg);
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "7: previous gm msg = %d", myDFP->m_goodMorningMsg);
      bt->println(buf);
    }
#endif

    myDFP->dfp.playFolder(1, myDFP->m_goodMorningMsg);
    break;

  case _oito: // IR remote control menu

#ifdef _DEBUG
    Serial.println("8: MENU");
#endif
#ifdef _DEBUG_BT
    bt->println("8: MENU");
#endif

    myDFP->dfp.playFolder(4, 1);
    break;

  case _nove: // next good morning message

    (myDFP->m_goodMorningMsg < myDFP->m_nGoodMorningMsgFiles) ? myDFP->m_goodMorningMsg++ : myDFP->m_goodMorningMsg = 1;

#ifdef _DEBUG
    Serial.print("9: next gm msg = "); Serial.println(myDFP->m_goodMorningMsg);
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "9: next gm msg = %d", myDFP->m_goodMorningMsg);
      bt->println(buf);
    }
#endif

    myDFP->dfp.playFolder(1, myDFP->m_goodMorningMsg);
    break;

  case _ok: // stop Roberto

#ifdef _DEBUG
    Serial.println("ok: stop");
#endif
#ifdef _DEBUG_BT
    bt->println("ok: stop");
#endif

    Roberto->stopMove();
    break;

  case _frente: // move Roberto forward

#ifdef _DEBUG
    Serial.println("^: forward");
#endif
#ifdef _DEBUG_BT
    bt->println("^: forward");
#endif

    Roberto->moveForward();
    break;

  case _tras: // move Roberto backward

#ifdef _DEBUG
    Serial.println("v: backward");
#endif
#ifdef _DEBUG_BT
    bt->println("v: backward");
#endif

    Roberto->moveBackward();
    break;

  case _direita: // turn Roberto right and stop

#ifdef _DEBUG
    Serial.println("-> turn right");
#endif
#ifdef _DEBUG_BT
    bt->println("-> turn right");
#endif

    Roberto->turnRight();

    /**** alteracao 2v2 **/
    Roberto->stopMove();
    /*********************/

    break;

  case _esquerda: // turn Roberto left and stop

#ifdef _DEBUG
    Serial.println("<- turn left");
#endif
#ifdef _DEBUG_BT
    bt->println("<- turn left");
#endif

    Roberto->turnLeft();

    /**** alteracao 2v2 **/
    Roberto->stopMove();
    /*********************/

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

//""""""""""""""""""""""""

void IR::checkIRCommand()
{
#ifdef _DEBUG
  // Serial.println("checkIRCommand()");
  // BT.println("checkIRCommand()");
#endif

  if (robertoState != CarState::bluetooth)
  {
    if (receptor.decode(&comando))
    {
      /***************** alteracao v2.2   ***/

      if (comando.value == _asterisco // turn ON/OFF remote control
          || comando.value == _velha  // turn ON/OFF radio
          || comando.value == _quatro // previous music
          || comando.value == _seis   // next music
          || comando.value == _cinco  // pause/restart music
          || comando.value == _um     // volume down
          || comando.value == _tres   // volume up
          || comando.value == _sete   // previous gm msg
          || comando.value == _nove   // next gm msg
          || comando.value == _oito   // menu
        ) 
      {
        execIRCommand();
      }

      /*****************/

      receptor.resume();

      /************* alteracao v2.2   ****/
      delay(10); // delay for resume
      /*****************/
    }
    IRcommandLoop();
  }
}

//"""""""""""""""""""""""" loop methods

void IR::IRcommandLoop()
{
  while (robertoState == CarState::remoteControl)
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
  if (myDFP->m_radioON && !myDFP->m_isPaused && millis() - m_IRLastTimeInLoop > m_IRLoopTimeout)
  {

#ifdef _DEBUG
    Serial.print("radio loop: busy pin = ");
    Serial.println(myDFP->readBusyPin());
#endif
#ifdef _DEBUG_BT
    {
      char buf[20];
      sprintf(buf, "radio loop: busy pin = %d", myDFP->readBusyPin());
      // detach servo to eliminate conflict during BT transmit
      Roberto->radarDetach();
      bt->println(buf);
      Roberto->radarAttach();

    }
#endif

    if (myDFP->readBusyPin())
    {
      comando.value = _seis;
      execIRCommand();
    }
    m_IRLastTimeInLoop = millis();
  }
}
