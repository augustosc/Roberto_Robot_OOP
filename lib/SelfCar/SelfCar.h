#ifndef _SELFCAR_H
#define _SELFCAR_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "RadarCar.h"
#include "CarState.h"


//""""""""""""""""""""""""class

/// @brief class selfCar inherit from RadarCar, plus bluetooth
class SelfCar : public RADARCAR::RadarCar
{

//""""""""""""""""""""""""private object aggregation
private:
    SoftwareSerial *bt;
    CarState m_carState {};


//"""""""""""""""""""""""" constructor declaration
public:
    /// @brief constructor self drive car
    /// @param _bt bluetooth object for debug
    SelfCar(SoftwareSerial *_bt);


//"""""""""""""""""""""""" public member functions

    /// @brief scan obstacles ahead and make the turn if necessary
    void scanAhead();

    /// @brief scan obstacles front (ahead and diagonals) and make the turn if necessary
    void scanFront();

    /// @brief make the corect turn to avoid obstacle
    void makeTheTurn();



//"""""""""""""""""""""""" public delegate functions

    /// @brief turn Roberto right with BT debug message
    void turnRight();

    /// @brief turn Roberto left with BT debug message
    void turnLeft();



//"""""""""""""""""""""""" public Car state functions

    /// @brief updates state of the car
    /// @param newState automatic, onBtControl or onIrControl
    void updateState(CarState newState){
        m_carState = newState;
    }

    /// @brief get state of the car
    /// @return state: automatic, onBtControl or onIrControl
    const CarState getState(){
        return m_carState;
    }


};

#endif //_SELFCAR_H
