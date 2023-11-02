/*!
 * @file SefCar.cpp
 * @brief Robot Roberto - An Arduino robot car 
 *
 * @copyright	Augusto Sherman
 * @copyright	GNU Lesser General Public License
 *
 * @author [Augusto Sherman](augusto.sherman@gmail.com)
 * @version  V3.0
 * @date  2023-11-02
 */

#include "SelfCar.h" 

  /**""""""""""""""""""""""""
     * Use _DEBUG_BT ONLY temporarily and disable _DEBUG_BT in BT.cpp
    */
    //#define _DEBUG
    //#define _DEBUG_BT



    //"""""""""""""""""""""""" constructor definition

    SelfCar::SelfCar(SoftwareSerial* _bt) 
     : bt{_bt}
    {}
    

    //"""""""""""""""""""""""" move delegate functions

    void SelfCar::turnRight()
    {
        #ifdef _DEBUG
          Serial.println("-> make turn right");
        #endif
        #ifdef _DEBUG_BT
        {
          char buf[50];
          sprintf(buf,"-> make turn right: h = %d, dr = %d, dl = %d",
          (int)obstacle.distance[RADARCAR::head],
          (int)obstacle.distance[RADARCAR::diagRight],
          (int)obstacle.distance[RADARCAR::diagLeft]);
          
          radarDetach();
          bt->println(buf);
          radarAttach();
        }
        #endif

        RadarCar::turnRight();
    }

    //""""""""""""""""""""""""

    void SelfCar::turnLeft()
    {
        #ifdef _DEBUG
          Serial.println("<- make turn left");
        #endif
        #ifdef _DEBUG_BT
        {
          char buf[50];
          sprintf(buf,"-> make turn left: h = %d, dr = %d, dl = %d",
          (int)obstacle.distance[RADARCAR::head],
          (int)obstacle.distance[RADARCAR::diagRight],
          (int)obstacle.distance[RADARCAR::diagLeft]);
          
          radarDetach();
          bt->println(buf);
          radarAttach();

        }
        #endif

        RadarCar::turnLeft();
    }

    //""""""""""""""""""""""""

    void SelfCar::makeTheTurn()
    {
      shouldTurnRight() ? turnRight() : turnLeft();
    }



    //""""""""""""""""""""""""self drive member functions
    
    void SelfCar::scanAhead(){
        mapAhead();

        // check timeout of playing stop message on pause
        checkStopMsgOnPause();
        
        #ifdef _DEBUG
         {
            char buf[50];
            sprintf(buf,"scan head: h = %d, oc=%c",(int)obstacle->distance[RADARCAR::head],obstacle->isClose ? 'y' : 'n');
             Serial.println(buf);
          }
        #endif
        
        if(obstacle.isClose)  {
          makeTheTurn();
        }
    }

    //""""""""""""""""""""""""

    void SelfCar::scanFront(){
        mapFront();
        //obstacle = Roberto.getObstacleInfo();

        #ifdef _DEBUG
        {
          char buf[50];
          sprintf(buf,"scan front: h = %d, dr = %d, dl = %d, oc = %c",
          (int)obstacle->distance[RADARCAR::head],
          (int)obstacle->distance[RADARCAR::diagRight],
          (int)obstacle->distance[RADARCAR::diagLeft],
          obstacle->isClose ? 'y' : 'n');
          Serial.println(buf);
        }
        #endif
        #ifdef _DEBUG_BT
        {
          char buf[50];
          sprintf(buf,"scan front: h = %d, dr = %d, dl = %d, oc = %c",
          (int)obstacle.distance[RADARCAR::head],
          (int)obstacle.distance[RADARCAR::diagRight],
          (int)obstacle.distance[RADARCAR::diagLeft],
          obstacle.isClose ? 'y' : 'n');

          radarDetach();
          bt->println(buf);
          radarAttach();

        }
        #endif

        if(obstacle.isClose)  {
          makeTheTurn();
        }

    }

    
    

    
    
