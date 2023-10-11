#ifndef _DFPGPIO_H
#define _DFPGPIO_H

#include <Arduino.h>

namespace DfpGpio {
    // DFPlayer control pins

    constexpr uint8_t dfpRxPin    {10};
    constexpr uint8_t dfpTxPin    {9};
    constexpr int busyPin         {8};

}

#endif