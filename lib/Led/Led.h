/*!
 * @file Led.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#ifndef _LED_H
#define _LED_H

#include <Arduino.h>

namespace LED
{

  //"""""""""""""""""""""""" class

  /// @brief manage Roberto remote control led
  class Led
  {

  //"""""""""""""""""""""""" constructor declaration
  public:
    /// @brief Led constructor
    /// @param pin led pin
    /// @param reverse reverse logic
    Led(uint8_t pin, bool reverse);



    //"""""""""""""""""""""""" public member functions

    /// @brief init led gpio
    void begin();

    /// @brief turn led on
    void on();

    /// @brief turn led off
    void off();

    /// @brief toggle led
    void toggle();

    /// @brief blink led
    /// @param interval blinking interval
    void blink(const unsigned long interval);

  
  
  //""""""""""""""""""""""""private data members
  private:
    uint8_t m_pin;                    ///< led pin
    bool m_reverse;                   ///< reverse logic
    uint8_t m_state;                  ///< led state
    unsigned long m_previousToggleTime{}; ///< time in ms of last toggle
  };

} // namespace LED

#endif // _LED_H