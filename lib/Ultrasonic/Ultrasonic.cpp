
#include "Ultrasonic.h"

const int debug {0};


Ultrasonic::Ultrasonic(int trigPin, int echoPin) 
  : m_trigPin{trigPin}, m_echoPin{echoPin}
{
  pinMode(m_trigPin, OUTPUT);
  pinMode(m_echoPin, INPUT);
}


float Ultrasonic::getDistance()
{

 float distance{};

  digitalWrite(m_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(m_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(m_trigPin, LOW);
  distance=pulseIn(m_echoPin,HIGH)*0.01724;
  delay(30);

      
if (distance > distMax) distance=30; 

 if (debug) 
{
  Serial.print("getDistance: ");
  Serial.println(distance);
}

 return distance;

     
}
