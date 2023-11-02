/*!
 * @file BtGpio.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */

#ifndef _BTGPIO_H
#define _BTGPIO_H

#include <Arduino.h>

namespace BtGpio {
    // Bluetooth control pins
    
    constexpr uint8_t BTrxPin     {13}; ///< bluetooth object rx pin
    constexpr uint8_t BTtxPin     {12}; ///< bluetooth object tx pin
}

#endif