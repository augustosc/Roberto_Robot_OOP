#ifndef _LED_H
#define _LED_H

#include <Arduino.h>

namespace LED
{

  /// @brief manage Roberto remote control led
  class Led
  {

  private:
    uint8_t m_pin;                    ///< led pin
    bool m_reverse;                   ///< reverse logic
    uint8_t m_state;                  ///< led state
    unsigned long m_previousToggle{}; ///< time in ms of last toggle

  public:
    /// @brief Led constructor
    /// @param pin led pin
    /// @param reverse reverse logic
    Led(uint8_t pin, bool reverse);

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
  };

} // namespace LED

#endif // _LED_H