#ifndef _MOTORGPIO_H
#define _MOTORGPIO_H

#include <Arduino.h>


#define _MPU_6050       // Comment for Roberto without MPU_6050

namespace MotorGpio {
    // Motors Control pins

    constexpr uint8_t mEpin1    {A3};     
    constexpr uint8_t mEpin2    {A2};
    #ifdef _MPU_6050
        constexpr uint8_t mDpin1 {A0};    
        constexpr uint8_t mDpin2 {A1};
    #else
        constexpr uint8_t mDpin1 {A4};
        constexpr uint8_t mDpin2 {A5};
    #endif
    constexpr uint8_t mDhab       {5};
    constexpr uint8_t mEhab       {6};

}

#endif //_MOTORGPIO_H