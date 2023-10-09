
#include "Arduino.h"
#include "Piloto.h"
#include "Dfplayer.h"
#include "IRcontrol.h"
#include "MyPins.h"




//--------------------------- globals
unsigned long timeout;
unsigned long timeNow;
const unsigned long tScanFront{700};



/// @brief Roberto states
enum carState {remoteControl, bluetooth, automatic};
extern enum carState robertoState; 
enum carState robertoState = automatic;  ///< initial Roberto state
  
// ---------------------- Create objects

Dfplayer myDFP (dfpRxPin, dfpTxPin, busyPin);

RadarCar Roberto(&myDFP);

Piloto Senna (Roberto);

IRcontrol myIR(irPin, &Roberto, &myDFP);

/////////////////////////////////////////////////////////
void setup() {
  
  // init hardware serial
  Serial.begin(115200);
  
  // init Roberto in automtic mode
  //robertoState=automatic;
  initLedControl();
  ledControlOFF();
 
  // do not attach servo inside class constructor
  // attaching the servo inside the main script setup() 
  Roberto.radarAttach();

  // init IRremote control
  myIR.begin();


  // init DFPlayer
  myDFP.begin();

  // set initial motor speed
  Roberto.setMotorSpeed(bothMotors,115);
  Roberto.setTurnSpeed(135);
  
  Roberto.lookAhead();
  delay(100);

  // better random
  randomSeed(micros() % 43);

  // Good Morning
  myDFP.sendGoodMorning();
  delay(500);

  // init timeout to scanFrot()
  timeout=millis();
}

//////////////////////////////////////////////////////////
void loop() {
  
  //-----------------------scan ahead
  Senna.scanAhead();
  Senna.moveForward();

  //-----------------------checK IR and BT
  myIR.checkIRCommand();
  //myBT.checKBTCommand();

  //-----------------------scan front each 700ms

  timeNow = millis();

  if (timeNow - timeout > tScanFront) 
  {
    timeout = timeNow;
    Senna.scanFront();
    Senna.moveForward();
  }
  
  delay(15);
  
}
////////////////////////////////////////////////////////////