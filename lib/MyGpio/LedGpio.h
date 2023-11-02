/*!
 * @file LedGpio.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */

#ifndef _LEDGPIO_H
#define _LEDGPIO_H

#include <Arduino.h>

namespace LedGpio {
    // Led pin

    constexpr uint8_t ledControlPin {11};   ///< remote control led pin
}
#endif //_LEDGPIO_H