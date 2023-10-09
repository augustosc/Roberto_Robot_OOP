#include <Arduino.h>
#include "IRcontrol.h"
#include "Dfplayer.h"
#include "MyPins.h"

// structure declarations
enum carState {remoteControl, bluetooth, automatic};

// internal constants
const int debug {1};
static unsigned long timeOutRadio;    ///< timeout to check busyPin

// external objects
extern enum carState robertoState;

// keys of IRcontrol KEYS/LAFVIN
const unsigned long _um        = 0xFF6897; 
const unsigned long _dois      = 0xFF9867;
const unsigned long _tres      = 0xFFB04F;
const unsigned long _quatro    = 0xFF30CF;
const unsigned long _cinco     = 0xFF18E7;
const unsigned long _seis      = 0xFF7A85;
const unsigned long _sete      = 0xFF10EF;
const unsigned long _oito      = 0xFF38C7;
const unsigned long _nove      = 0xFF5AA5;
const unsigned long _zero      = 0xFF4AB5;
const unsigned long _asterisco = 0xFF42BD;
const unsigned long _velha     = 0xFF52AD;
const unsigned long _ok        = 0xFF02FD;
const unsigned long _frente    = 0xFF629D;
const unsigned long _tras      = 0xFFA857;
const unsigned long _direita   = 0xFFC23D;
const unsigned long _esquerda  = 0xFF22DD;
const unsigned long _dup       = 0xFFFFFFFF;

//""""""""""""""""""""""""""""""""
void IRcontrol::begin()
{
    receptor.enableIRIn();
}


//"""""""""""""""""""""""""""""""""
void IRcontrol::execIRCommand () 
{
  switch (comando.value) { 

      case _asterisco:      // if command == '*', turn ON/OFF remote contro mode
        if (debug) {
          Serial.println("'*', remote control mode ON/OFF");
          //BT.println("'*', remote control mode ON/OFF");
        }
 
        if (robertoState == automatic) 
        {
          robertoState=remoteControl;
          if (debug) Serial.println("remote control mode");
        }
        else 
        {
          robertoState=automatic;
          if (debug) Serial.println("automatic mode");
        }
        if (robertoState == remoteControl) 
        {
          Roberto->stopMove();
          if (debug) Serial.println("Led ON");
          ledControlON();
        }
        else 
        {
          if (debug) Serial.println("Led OFF");
          ledControlOFF();
        }
      break;
      
      case _velha:       //if command == #, turn ON/OFF radio
        if (debug) {
          Serial.println("#, turn ON/OFF radio");
          //BT.println("#, turn ON/OFF radio");
        }
        myDFP->musicaAtual=random(1,myDFP->nArqvMp3+1);
        myDFP->radioON=!myDFP->radioON;
        if (myDFP->radioON) {
          myDFP->dfp.playMp3Folder(myDFP->musicaAtual);
        }
        else {
          myDFP->dfp.pause();
        }
      break;

      case _um:         // Volume -
        if (debug) {
          Serial.println("'1' Volume -");
          //BT.println("'1' Volume -");
        }
        if (myDFP->volumeAtual > 5) {
          myDFP->volumeAtual--;
          myDFP->dfp.volumeDown();
        }
      break;
      
      case _tres:      // Volume +
        if (debug) {
          Serial.println("'3' Volume+");
          //BT.println("'3' Volume+");
        }
        if (myDFP->volumeAtual < 30) {
          myDFP->volumeAtual++;
          myDFP->dfp.volumeUp();
        }
      break;

      case _quatro:    // previous music
        if (debug) {
          Serial.println("'4' previous music");
          //BT.println("'4' previous music");
        }
        if (myDFP->musicaAtual > 1) {
          myDFP->musicaAtual--;
        }
        else {
          myDFP->musicaAtual=myDFP->nArqvMp3;
        }
        myDFP->dfp.playMp3Folder(myDFP->musicaAtual);
        myDFP->radioON=1;
      break;

      case _cinco:    // pause music
        if (debug) {
          Serial.println("'5' pause music");
          //BT.println("'5' pause music");
        }
        myDFP->pauseRadio=!myDFP->pauseRadio;
        if (myDFP->pauseRadio) {
          myDFP->dfp.pause();
          
        }
        else {
          myDFP->dfp.start();
          delay(150);
          
        }
        myDFP->radioON=1;
      break;

      case _seis:        // next music
        if (debug) {
          Serial.println("'6' next music");
          //BT.println("'6' next music");
        }
        if (myDFP->musicaAtual < myDFP->nArqvMp3) {
          myDFP->musicaAtual++; 
          
          if (debug) 
          {
            Serial.print("musica atual: "); Serial.println(myDFP->musicaAtual);
          }         
        }
        else {
          myDFP->musicaAtual=1;
        }
        myDFP->dfp.playMp3Folder(myDFP->musicaAtual);
        myDFP->radioON=1;
      break;
        
      
      case _sete:       // msg -
        if (debug) {
          Serial.println("'7' msg -");
          //BT.println("'7' msg -");
        }
        if (myDFP->msgBomDia > 1) myDFP->msgBomDia--;
        else myDFP->msgBomDia=myDFP->nArqvMsgBomDia;
        myDFP->dfp.playFolder(1,myDFP->msgBomDia); 
      break;

      case _oito:       // menu
          if (debug) {
            Serial.println("'8' MENU");
            //BT.println("'8' MENU");
          }
          myDFP->dfp.playFolder(4,1);
      break;
      
      case _nove:      // msg +
        if (debug) {
          Serial.println("'9' msg +");
          //BT.println("'9' msg +");
        }
        if (myDFP->msgBomDia < myDFP->nArqvMsgBomDia) myDFP->msgBomDia++;
        else myDFP->msgBomDia=1;
        myDFP->dfp.playFolder(1,myDFP->msgBomDia);
      break;
      
      case _ok:        // stop Roberto
        if (debug) {
          Serial.println("'ok' stop");
          //BT.println("'ok' stop");
        }
        Roberto->stopMove();
      break ;
      
      case _frente:    // move Roberto forward
        if (debug) {
          Serial.println("forward");
          //BT.println("forward");
        }
        Roberto->moveForward();
      break ;

      case _tras:      // backward, move Roberto backward
        if (debug) {
          Serial.println("backward");
          //BT.println("backward");
        }
        Roberto->moveBackward();
      break ;
      
      case _direita:   // turn Roberto right and stop
        if (debug) {
          Serial.println("'->' right");
          //BT.println("'->' right");
        }
        Roberto->turnRight();
          
        /**** alteracao 2v2 **/
        Roberto->stopMove();                
        /*********************/
        
      break ;
      
      case _esquerda:        // turn Roberto left and stop
        if (debug) {
          Serial.println("'<-' esquerda");
          //BT.println("'<-' esquerda");
        }
        Roberto->turnLeft();
          
        /**** alteracao 2v2 **/
        Roberto->stopMove();
        /*********************/
        
        break ;
              
      case _dup:
      break;
              
      default:         //// ignore other comands
        if (debug) {
          Serial.print("outro: 0x");
          Serial.println(comando.value,HEX);
          //BT.print("outro: 0x");
          //BT.println(comando.value,HEX);
        }
        
      break ;
    }
    
}

void IRcontrol::radioInLoop ()
{
  if (debug) {
        //Serial.println("radioInLoop ()");
        //BT.println("radioEmLoop ()");
      }
  // check busyPin each 3s and,if that's the case, change music
  // busypin == LOW when playing
  if (myDFP->radioON &&  !myDFP->pauseRadio && millis() - timeOutRadio > 3000) {

                if (debug) {
                  //Serial.print("type: 0x");Serial.print(myDFP->dfp.readType(),HEX);
                  //BT.print("type: 0x");Serial.print(dfp.readType(),HEX);
                }
                if (debug) {
                  //Serial.print(" --- Busy State: ");Serial.println(digitalRead(busyPin));
                  //BT.print(" --- Busy State: ");Serial.println(digitalRead(busyPin));
                }
    if (digitalRead(myDFP->m_busyPin))  {
      comando.value=_seis;
      execIRCommand();
    }
    timeOutRadio=millis();
  }

}


//""""""""""""""""""""""""""""""""
void IRcontrol::checkIRCommand() 
{
  if (debug) {
    //Serial.println("checkIRCommand()");
    //BT.println("checkIRCommand()");
    }
  
  
  if (robertoState != bluetooth) 
  {
    if (receptor.decode(&comando)){
      /***************** alteracao v2.2   ***/
      
      if (comando.value == _asterisco    // turn ON/OFF remote control
        || comando.value == _velha       // turn ON/OFF radio
        || comando.value == _seis        // Mus+
        || comando.value == _cinco)      // pause music
        {
          execIRCommand ();
        }
          
      /*****************/
      
      receptor.resume();

      /************* alteracao v2.2   ****/
      delay(10);                               // delay for resume
      /*****************/
    }
  
    while(robertoState == remoteControl){
      if (receptor.decode(&comando)){
        if (comando.value != _dup) execIRCommand(); 
        receptor.resume(); 
      }
      radioInLoop();

      /*****************/
      delay(100);                   //break loop
      /*****************/
    }
  } 
}