#ifndef _BTGPIO_H
#define _BTGPIO_H

#include <Arduino.h>

namespace BtGpio {
    // Bluetooth control pins
    
    constexpr uint8_t BTrxPin     {13}; ///< bluetooth object rx pin
    constexpr uint8_t BTtxPin     {12}; ///< bluetooth object tx pin
}

#endif