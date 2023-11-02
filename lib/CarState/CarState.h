/*!
 * @file CarState.h
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */


#ifndef _CARSTATE_H
#define _CARSTATE_H


//"""""""""""""""""""""""" instance in main.cpp

    /// @brief possible Roberto states
    enum class CarState {
        onIrControl, 
        onBtControl, 
        automatic
    };


#endif //_CARSTATE_H