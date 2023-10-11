#ifndef _BTGPIO_H
#define _BTGPIO_H

#include <Arduino.h>

namespace BtGpio {
    // Bluetooth control pins
    
    constexpr uint8_t BTrxPin     {13};
    constexpr uint8_t BTtxPin     {12};
}

#endif