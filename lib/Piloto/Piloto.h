#ifndef _PILOTO_h
#define _PILOTO_h

#include "Arduino.h"
#include "RadarCar.h"

/// @brief Piloto class with Roberto (the radarCar)
class Piloto {
private:
    RadarCar Roberto;
    struct  obstacleInfo *obstacle;

public:

    Piloto (RadarCar& Roberto);
    
    /// @brief move Roberto forward
    void moveForward();

    /// @brief move Roberto forward
    void moveBackward();

    /// @brief turn Roberto right
    void turnRight();

    /// @brief turn Roberto left
    void turnLeft();

    /// @brief stop Roberto
    void stopMove();

    /// @brief Roberto look ahead
    void lookAhead();
    
    /// @brief scan obstacles ahead and turn if necessary
    void scanAhead();

    /// @brief scan obstacles front (ahead and diagonals) and turn if necessary
    void scanFront();

    /// @brief attach servo motor
    void radarAttach();

    /// @brief get obstacle distance info
    /// @return obstacle Info struct pointer
    struct obstacleInfo * getObstacleInfo();
    
    
};

#endif
