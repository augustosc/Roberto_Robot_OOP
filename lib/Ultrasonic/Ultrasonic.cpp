
#include "Ultrasonic.h"



Ultrasonic::Ultrasonic(int trigPin, int echoPin) 
  : m_trigPin{trigPin}, m_echoPin{echoPin}
{
  pinMode(m_trigPin, OUTPUT);
  pinMode(m_echoPin, INPUT);
}

float Ultrasonic::getDistance(){
//  float duration, distance;
//  digitalWrite(m_trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(m_trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(m_trigPin, LOW);
//
//  duration = pulseIn(m_echoPin, HIGH);
//  distance = (duration*.0343)/2;
//  return distance;


    int random = (rand() % 200);

    return static_cast< float >(20+random);
     
}
