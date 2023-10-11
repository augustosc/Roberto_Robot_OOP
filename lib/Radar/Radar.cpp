#include "Radar.h"

namespace RADAR
{

  //"""""""""""""""""""""""" constructor

  Radar::Radar(const uint8_t trigPin, const uint8_t echoPin, const int servoPin, const int pulseMin, const int pulseMax)
      : ultrasonic{trigPin, echoPin}, m_servoPin{servoPin}, m_pulseMin{pulseMin}, m_pulseMax{pulseMax}
  {
    // do not attach servo inside class constructor
    // attaching the servo inside the main script setup()
  }

  //"""""""""""""""""""""""" get distance methods

  float Radar::getDistanceAhead(int _delay)
  {
    servo.write(m_Position.head);
    delay(_delay);
    return ultrasonic.getDistance();
  }

  //""""""""""""""""""""""""

  float Radar::getDistanceRight(int _delay)
  {
    servo.write(m_Position.right);
    delay(_delay);
    return ultrasonic.getDistance();
  }

  //""""""""""""""""""""""""

  float Radar::getDistanceDiagRight(int _delay)
  {
    servo.write(m_Position.diagRight);
    delay(_delay);
    return ultrasonic.getDistance();
  }

  //""""""""""""""""""""""""

  float Radar::getDistanceLeft(int _delay)
  {
    servo.write(m_Position.left);
    delay(m_servoDelay);
    return ultrasonic.getDistance();
  }

  //""""""""""""""""""""""""

  float Radar::getDistanceDiagLeft(int _delay)
  {
    servo.write(m_Position.diagLeft);
    delay(_delay);
    return ultrasonic.getDistance();
  }

  //"""""""""""""""""""""""" servo methods

  int Radar::moveServo(int angle)
  {
    servo.write(angle);
    return servo.read();
  }

  //""""""""""""""""""""""""

  void Radar::attach()
  {
    m_servoID = servo.attach(m_servoPin, m_pulseMin, m_pulseMax);
  }

  //""""""""""""""""""""""""

  void Radar::detach()
  {
    servo.detach();
  }


  //""""""""""""""""""""""""

  bool Radar::isAttached()
  {
    return servo.attached();
  }

  //""""""""""""""""""""""""

  int Radar::getServoID()
  {
    return m_servoID;
  }

  //""""""""""""""""""""""""

  void Radar::lookAhead()
  {
    moveServo(m_Position.head);
    delay(m_servoDelay);
  }

} // namespace RADAR
