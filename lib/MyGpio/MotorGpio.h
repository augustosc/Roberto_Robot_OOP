#ifndef _MOTORGPIO_H
#define _MOTORGPIO_H

#include <Arduino.h>


#define _MPU_6050       // Comment for Roberto without MPU_6050

namespace MotorGpio {
    // Motors Control pins

    constexpr uint8_t mEpin1    {A3};       ///< L298D left motor pin1  
    constexpr uint8_t mEpin2    {A2};       ///< L298D left motor pin2
    #ifdef _MPU_6050
        constexpr uint8_t mDpin1 {A0};      ///< L298D right motor pin1
        constexpr uint8_t mDpin2 {A1};      ///< L298D right motor pin2
    #else
        constexpr uint8_t mDpin1 {A4};      ///< L298D right motor pin1
        constexpr uint8_t mDpin2 {A5};      ///< L298D right motor pin2
    #endif
    constexpr uint8_t mDhab       {5};      ///< PWM control pin right motor
    constexpr uint8_t mEhab       {6};      ///< PWM control pin left motor

}

#endif //_MOTORGPIO_H