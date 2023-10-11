#include "Led.h"

namespace LED
{

  //"""""""""""""""""""""""" constructor

  Led::Led(uint8_t pin, bool reverse = false)
      : m_pin{pin}, m_reverse{reverse}
  {
    begin();
  }

  //""""""""""""""""""""""""

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
    if (now - m_previousToggle > interval)
    {
      toggle();
      m_previousToggle = now;
    }
  }
} // namespace LED