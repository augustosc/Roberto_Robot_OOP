#ifndef _PILOTO_h
#define _PILOTO_h

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "RadarCar.h"

/// @brief drives Roberto Car
class Piloto
{
private:
    RADARCAR::RadarCar Roberto;
    struct RADARCAR::obstacleInfo *obstacle;
    SoftwareSerial *bt;

public:
    /// @brief drives Roberto
    /// @param Roberto Car object by aggregation
    /// @param _bt bluetooth object by aggregation
    Piloto(RADARCAR::RadarCar &Roberto, SoftwareSerial *_bt);

    /// @brief move Roberto forward
    void moveForward();

    /// @brief move Roberto forward
    void moveBackward();

    /// @brief turn Roberto right
    void turnRight();

    /// @brief turn Roberto left
    void turnLeft();

    /// @brief make the turn to avoid obstacle
    void makeTheTurn();

    /// @brief stop Roberto
    void stopMove();

    /// @brief Roberto look ahead
    void lookAhead();

    /// @brief scan obstacles ahead and make the turn if necessary
    void scanAhead();

    /// @brief scan obstacles front (ahead and diagonals) and make the turn if necessary
    void scanFront();

    /// @brief attach servo motor
    void radarAttach();

    /// @brief get obstacle distance info
    /// @return obstacle Info struct pointer
    struct RADARCAR::obstacleInfo *getObstacleInfo();
};

#endif
