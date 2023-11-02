/*!
 * @file UltraGpio.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#ifndef _ULTRAGPIO_H
#define _ULTRAGPIO_H
#include <Arduino.h>

namespace UltraGpio {
    // Ultrasonic control pins

    constexpr uint8_t trigPin  {3};     ///< ultrasonic trigger pin
    constexpr uint8_t echoPin  {2};     ///< ultrasonic echoPin
}
#endif //_ULTRAGPIO_H