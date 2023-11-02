/*!
 * @file main.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 * 
 * 
 * **********************************************************************************
 * Start of work:   2020-10-22.
 * Final Version 2.0, 2021-08-01.
 * Final Version 3.0, 2023-11-02
 * 
 * 
 * ROBOT ROBERTO was built for Ana Clara, Giovanna, Gabriel and all the grandchildren that come along. The daughters and Cida will be able to enjoy.
 * 
 * The objective was still to provide Ana Clara, in Canada, with the affection of part of her family who is in Brazil.
 * 
 * To this end, numerous "good morning" messages from many family members were inserted to her, so that she has certainty that, even far away, we are close to her. She can listen to these messages whenever she wants through Roberto.
 * 
 * It is also a souvenir that Grandpa Sherman leaves, of his work, for his grandchildren. Every weld, every screw, every component, each thread, each line of this code had moments of effort, imagination, reflection and study by grandpa, to overcome the difficulties of building Roberto.
 * 
 * In addition, there is grandpa's message to his grandchildren that to build something, even if it is a small robot, effort, work, obstinacy is necessary. I would like that my grandchildren had this awareness.
 * 
 * AUGUSTO SHERMAN, 8/01/2021
 * 
 */


#include "Arduino.h"
#include "SoftwareSerial.h"
#include "SelfCar.h"
#include "Dfplayer.h"
#include "IR.h"
#include "Led.h"
#include "BT.h"
#include "CarState.h"
#include "DfpGpio.h"
#include "LedGpio.h"
#include "BtGpio.h"




//"""""""""""""""""""""""" my objects

SoftwareSerial Bluetooth(BtGpio::BTrxPin, BtGpio::BTtxPin);

LED::Led ledControl(LedGpio::ledControlPin, true);

SelfCar Roberto(&Bluetooth);

BT myBT(&Roberto, &ledControl, &Bluetooth);

IR myIR(&Roberto, &ledControl, &Bluetooth);



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

  // init Roberto in automatic mode
  Roberto.updateState(CarState::automatic);

  // set initial motor speed
  Roberto.setMotorSpeed(115);
  Roberto.setTurnSpeed(135);

  // init DFPlayer
  Roberto.myDFP.begin();

  // init IR remote control
  myIR.begin();

  // better random
  randomSeed(micros() % 43);

  // play Good Morning message
  Roberto.myDFP.playGoodMorningMsg();
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
  Roberto.scanAhead();
  Roberto.moveForward();

  //"""""""""""""""""""""""" checK IR or BT command
  myIR.checkIRCommand();
  myBT.checkBTcommand();

  //"""""""""""""""""""""""" scan front each 700ms
  timeNow = millis();

  if (timeNow - lastScanTime > ScanFrontTimeout)
  {
    lastScanTime = timeNow;
    Roberto.scanFront();
    Roberto.moveForward();
  }

  delay(15);
}
////////////////////////////////////////////////////////////