#include "MyPins.h"

#define _MPU_6050    // descomente para Roberto com MPU6050


extern const int trigPin  {3};  ///< ultrasonic trigPin
extern const int echoPin  {2};  ///< ultrasonic echoPin
extern const int servoPin {7};  ///< servo control pin
extern const int pulseMin {1000}; ///< servo pulse min
extern const int pulseMax {2000}; ///< servo pulse max

extern const int mEpin1 {A3};   ///< L298D left motor pin1     
extern const int mEpin2 {A2};   ///< L298D left motor pin2 
#ifdef _MPU_6050
extern const int mDpin1 {A0};  ///< L298D right motor pin1  (MPU6050)      
extern const int mDpin2 {A1};  ///< L298D right motor pin2  (MPU6050)
#else
extern const int mDpin1 {A4}; ///< L298D right motor pin1
extern const int mDpin2 {A5}; ///< L298D right motor pin2
#endif
extern const int mDhab  {5};    ///< PWM control pin right motor
extern const int mEhab  {6};    ///< PWM control pin left motor

extern const uint8_t dfpRxPin {10}; ///< DFP Rx pin
extern const uint8_t dfpTxPin {9};  ///< DFP Tx pin
extern const int busyPin      {8};  ///< DFP busyPin

// IRremote pins
extern const int irPin {4};         ///< IR pin
extern const int ledControl {11};   ///< remote control signaling led pin


 void initLedControl()
 {
    pinMode(ledControl, OUTPUT);
 }

void ledControlON()
{
    digitalWrite(ledControl,LOW);
}

void ledControlOFF()
{
    digitalWrite(ledControl,HIGH);
}


