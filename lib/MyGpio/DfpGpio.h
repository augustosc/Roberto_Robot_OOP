/*!
 * @file DfpGpio.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


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