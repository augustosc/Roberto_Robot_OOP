#include "Piloto.h" 

  
    //#define _DEBUG

    /**""""""""""""""""""""""""
     * Use _DEBUG_BT ONLY temporarily and disable _DEBUG_BT in BT.cpp
    */
    #define _DEBUG_BT

    //"""""""""""""""""""""""" constructor

    Piloto::Piloto(RADARCAR::RadarCar &Car,SoftwareSerial* _bt) 
    : Roberto{Car}, bt{_bt}
    {}
    
    //"""""""""""""""""""""""" move methods
    
    void Piloto::moveForward(){
        Roberto.moveForward();
    }

    //""""""""""""""""""""""""

    void Piloto::moveBackward(){
        Roberto.moveBackward();
    }

    //""""""""""""""""""""""""

    void Piloto::turnRight()
    {
        #ifdef _DEBUG
          Serial.println("-> make turn right");
        #endif
        #ifdef _DEBUG_BT
        {
          char buf[50];
          sprintf(buf,"-> make turn right: h = %d, dr = %d, dl = %d",
          (int)obstacle->distance[RADARCAR::head],
          (int)obstacle->distance[RADARCAR::diagRight],
          (int)obstacle->distance[RADARCAR::diagLeft]);
          
          Roberto.radarDetach();
          bt->println(buf);
          Roberto.radarAttach();

        }
        #endif

        Roberto.turnRight();
    }

    //""""""""""""""""""""""""

    void Piloto::turnLeft()
    {
        #ifdef _DEBUG
          Serial.println("<- make turn left");
        #endif
        #ifdef _DEBUG_BT
        {
          char buf[50];
          sprintf(buf,"-> make turn left: h = %d, dr = %d, dl = %d",
          (int)obstacle->distance[RADARCAR::head],
          (int)obstacle->distance[RADARCAR::diagRight],
          (int)obstacle->distance[RADARCAR::diagLeft]);
          
          Roberto.radarDetach();
          bt->println(buf);
          Roberto.radarAttach();

        }
        #endif

        Roberto.turnLeft();
    }

    //""""""""""""""""""""""""

    void Piloto::makeTheTurn()
    {
      Roberto.shouldTurnRight() ? turnRight() : turnLeft();
    }

    
    //""""""""""""""""""""""""

    void Piloto::stopMove(){
      Roberto.stopMove();
    }

    //"""""""""""""""""""""""" servo method

    void Piloto::radarAttach(){
      Roberto.radarAttach();
    }

    //"""""""""""""""""""""""" scan methods

    struct RADARCAR::obstacleInfo * Piloto::getObstacleInfo(){
      return Roberto.getObstacleInfo();
    }

    //""""""""""""""""""""""""

    void Piloto::lookAhead (){
      Roberto.lookAhead();
    }

    //""""""""""""""""""""""""
    
    void Piloto::scanAhead(){
        Roberto.mapAhead();
        obstacle = Roberto.getObstacleInfo();
        
        #ifdef _DEBUG
         {
            char buf[50];
            sprintf(buf,"scan head: h = %d, oc=%c",(int)obstacle->distance[RADARCAR::head],obstacle->isClose ? 'y' : 'n');
             Serial.println(buf);
          }
        #endif
        
        if(obstacle->isClose)  {
          makeTheTurn();
        }
    }

    //""""""""""""""""""""""""

    void Piloto::scanFront(){
        Roberto.mapFront();
        obstacle = Roberto.getObstacleInfo();

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
          (int)obstacle->distance[RADARCAR::head],
          (int)obstacle->distance[RADARCAR::diagRight],
          (int)obstacle->distance[RADARCAR::diagLeft],
          obstacle->isClose ? 'y' : 'n');

          Roberto.radarDetach();
          bt->println(buf);
          Roberto.radarAttach();

        }
        #endif

        if(obstacle->isClose)  {
          makeTheTurn();
        }
    }

    

    
    
