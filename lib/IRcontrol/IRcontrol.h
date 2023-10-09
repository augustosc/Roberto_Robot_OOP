#ifndef _IR_CTRL_H
#define _IR_CTRL_H

#include "IRremote.h"
#include "RadarCar.h"
#include "Dfplayer.h"

/// @brief manage Roberto IR remote control
class IRcontrol {
private:
     
    IRrecv receptor;        ///< IR receptor object
    decode_results comando; ///< results object
    RadarCar* Roberto;      ///< Roberto object
    Dfplayer* myDFP;        ///< DFP object

public:
    IRcontrol(int irPin, RadarCar* Car,Dfplayer* DFP)
    : receptor{irPin},comando{}, Roberto{Car}, myDFP{DFP}
    {}

    /// @brief execute IR command
    void execIRCommand ();


    /// @brief manage music in continuos mode
    void radioInLoop ();



    /// @brief check IR command
    void checkIRCommand();

    /// @brief init IR control
    void begin();

};




#endif //_IR_CTRL_H