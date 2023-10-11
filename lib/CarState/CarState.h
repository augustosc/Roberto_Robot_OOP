#ifndef _CARSTATE_H
#define _CARSTATE_H


//"""""""""""""""""""""""" instance in main.cpp

    /// @brief possible Roberto states
    enum class CarState {remoteControl, bluetooth, automatic};

    // external object CarState
    extern CarState robertoState; ///< instance in main.cpp



#endif //_CARSTATE_H