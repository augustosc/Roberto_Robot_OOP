#ifndef _DFPGPIO_H
#define _DFPGPIO_H

#include <Arduino.h>

namespace DfpGpio {
    // DFPlayer control pins

    constexpr uint8_t dfpRxPin    {10}; ///< DFP Rx pin
    constexpr uint8_t dfpTxPin    {9};  ///< DFP Tx pin
    constexpr int busyPin         {8};  ///< DFP busy pin

}

#endif