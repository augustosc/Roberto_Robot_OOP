#ifndef _PILOTO_h
#define _PILOTO_h

#include "Arduino.h"
#include "RadarCar.h"

class Piloto {
private:
    RadarCar Roberto;
    struct  obstacleMap *obstacle;

public:
    Piloto (RadarCar& Roberto);
    

    void moveForward();
    void moveBackward();
    void turnRight();
    void turnLeft();
    void stopMove();
    void lookAhead();
    
    void scanAhead();
    void scanFront();
    void radarAttach();
    struct obstacleMap * getObstacleInfo();
    
    
};

#endif
