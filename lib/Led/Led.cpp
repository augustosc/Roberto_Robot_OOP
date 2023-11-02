/*!
 * @file Led.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#include "Led.h"

namespace LED
{

  //"""""""""""""""""""""""" constructor definition

  Led::Led(uint8_t pin, bool reverse = false)
      : m_pin{pin}, m_reverse{reverse}
  {
    begin();
  }

  //""""""""""""""""""""""""public member functions

  void Led::begin()
  {
    pinMode(m_pin, OUTPUT);
    off();
  }

  //""""""""""""""""""""""""

  void Led::on()
  {

    digitalWrite(m_pin, m_reverse ? LOW : HIGH);
    m_state = 1;
  }

  //""""""""""""""""""""""""

  void Led::off()
  {
    digitalWrite(m_pin, m_reverse ? HIGH : LOW);
    m_state = 0;
  }

  //""""""""""""""""""""""""

  void Led::toggle()
  {
    m_state ? off() : on();
  }

  //""""""""""""""""""""""""

  void Led::blink(const unsigned long interval)
  {
    unsigned long now = millis();
    if (now - m_previousToggleTime > interval)
    {
      toggle();
      m_previousToggleTime = now;
    }
  }
} // namespace LED