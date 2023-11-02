/*!
 * @file ServoGpio.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#ifndef _SERVOGPIO_H
#define _SERVOGPIO_H

namespace ServoGpio {
    // Servo control pin and pulse configuration

    constexpr int servoPin     {7};     ///< servo control pin
    constexpr int pulseMin     {1000};  ///< servo pulse min
    constexpr int pulseMax     {2000};  ///< servo pulse max
}


#endif //_SERVOGPIO_H