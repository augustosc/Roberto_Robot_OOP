
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Piloto.h"
#include "Dfplayer.h"
#include "IR.h"
#include "Led.h"
#include "BT.h"
#include "CarState.h"
#include "DfpGpio.h"
#include "LedGpio.h"
#include "BtGpio.h"

//"""""""""""""""""""""""" set initial Roberto state
CarState robertoState{CarState::automatic};

//"""""""""""""""""""""""" my objects

SoftwareSerial Bt(BtGpio::BTrxPin, BtGpio::BTtxPin);

DFPLAYER::Dfplayer myDFP(DfpGpio::dfpRxPin, DfpGpio::dfpTxPin, DfpGpio::busyPin); 

RADARCAR::RadarCar Roberto(&myDFP); 

Piloto Senna(Roberto, &Bt);

LED::Led ledControl(LedGpio::ledControlPin, true);

BT myBT(&Roberto, &myDFP, &ledControl, &Bt);

IR myIR(&Roberto, &myDFP, &ledControl, &Bt);

/////////////////////////////////////////////////////////
void setup()
{
  // init hardware serial
  Serial.begin(115200);

  // do not attach servo inside class constructor
  // attaching the servo inside the main script setup()
  Roberto.radarAttach();

  // Positions radar ahead
  Roberto.lookAhead();

  // set initial motor speed
  Roberto.setMotorSpeed(115);
  Roberto.setTurnSpeed(135);

  // init DFPlayer
  myDFP.begin();

  // init IR remote control
  myIR.begin();

  // better random
  randomSeed(micros() % 43);

  // play Good Morning message
  myDFP.playGoodMorningMsg();
  delay(500);

  // init BT remote control
  myBT.begin(9600);
  delay(100);

  // set BT as listening
  myBT.listen();
}

//////////////////////////////////////////////////////////
void loop()
{

  constexpr unsigned long ScanFrontTimeout{700}; ///< scanFront timeout
  static unsigned long lastScanTime{millis()};   ///< used for scanFront timeout
  static unsigned long timeNow;                  ///< used for scanFront timeout

  //""""""""""""""""""""""""scan ahead
  Senna.scanAhead();
  Senna.moveForward();

  //"""""""""""""""""""""""" checK IR or BT command
  myIR.checkIRCommand();
  myBT.checkBTcommand();

  //"""""""""""""""""""""""" scan front each 700ms
  timeNow = millis();

  if (timeNow - lastScanTime > ScanFrontTimeout)
  {
    lastScanTime = timeNow;
    Senna.scanFront();
    Senna.moveForward();
  }

  delay(15);
}
////////////////////////////////////////////////////////////