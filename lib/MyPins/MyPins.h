#include <Arduino.h>


    extern const int trigPin;  ///< ultrasonic trigPin
    extern const int echoPin;  ///< ultrasonic echoPin
    extern const int pulseMin; ///< servo pulse min
    extern const int pulseMax; ///< servo pulse max
    extern const int servoPin;  ///< servo control pin
    extern const int mEpin1;    ///< L298D left motor pin1     
    extern const int mEpin2;    ///< L298D left motor pin2 
    extern const int mDpin1;    ///< L298D right motor pin1
    extern const int mDpin2;    ///< L298D right motor pin2
    extern const int mDhab;     ///< PWM control pin right motor
    extern const int mEhab;     ///< PWM control pin left motor
    extern const uint8_t dfpRxPin; ///< DFP Rx pin
    extern const uint8_t dfpTxPin;  ///< DFP Tx pin
    extern const int busyPin;    ///< DFP busyPin
    extern const int irPin;        ///< IR pin
    extern const int ledControl;   ///< remote control signaling led pin


    void initLedControl();
    void ledControlON();
    void ledControlOFF();