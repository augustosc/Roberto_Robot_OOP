#ifndef _ULTRAGPIO_H
#define _ULTRAGPIO_H
#include <Arduino.h>

namespace UltraGpio {
    // Ultrasonic control pins

    constexpr uint8_t trigPin  {3};
    constexpr uint8_t echoPin  {2};
}
#endif //_ULTRAGPIO_H