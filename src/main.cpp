/*
 * Piloto Class
 */

#include "Arduino.h"
#include "Piloto.h"

//-------------------------------------------------- globals
unsigned long timeout;
unsigned long timeNow;
const unsigned long tScanFrontal{4000};

// --------------------------------------------------- ultrasonic pins
const int trigPin = 9;
const int echoPin = 10;


// --------------------------------------------------- servo pin and pulse data
  const int servoPin = 7;
  const int pulseMin=1000;
  const int pulseMax=2000;

// --------------------------------------------------- motor pins to L298D
  const int mEpin1 =A3;                                  
  const int mEpin2 =A2;
  const int mDpin1 =A4;                                  
  const int mDpin2 =A5;
  const int mDhab = 5;
  const int mEhab = 6;
  
// --------------------------------------------------- create objects

RadarCar Roberto(mEpin1,mEpin2,mDpin1,mDpin2,mEhab,mDhab,trigPin,echoPin,servoPin,pulseMin,pulseMax);
Piloto Clarinha(Roberto);

/////////////////////////////////////////////////////////
void setup() {
  
  Serial.begin(9600);
  timeout=millis();

  // do not attach servo inside class constructor
  // attaching the servo inside the main script setup() 
  Roberto.radarAttach();
  
  Roberto.lookAhead();
  delay(200);
}

//////////////////////////////////////////////////////////
void loop() {
  int robertoVeloc;
  
  Serial.println("-------------------------");
  Serial.print("Clarinha is running at : ");Serial.println(Roberto.getMotorSpeed(bothMotors));
  
  //------------------------------- scan left
  Clarinha.scanAhead();
  Clarinha.moveForward();

  //------------------------------- scan frontal
  timeNow = millis();
  if (timeNow - timeout > tScanFrontal) {
    timeout = timeNow;
    
    robertoVeloc = Roberto.getMotorSpeed(bothMotors); // change velocity
    if ( robertoVeloc < 200) Roberto.setMotorSpeed(bothMotors, robertoVeloc+50);
    else Roberto.setMotorSpeed(bothMotors,130);
    
    Clarinha.scanFront();
  }
  
  delay(200);
  
}
////////////////////////////////////////////////////////////