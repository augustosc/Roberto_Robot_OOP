#include "Piloto.h" 


    Piloto::Piloto(RadarCar &Car) : Roberto{Car}
    {}
    
    void Piloto::moveForward(){
        Roberto.moveForward();
    }
    void Piloto::moveBackward(){
        Roberto.moveBackward();
    }
    void Piloto::turnRight(){
        Roberto.turnRight();
    }
    void Piloto::turnLeft(){
        Roberto.turnLeft();
    }

    void Piloto::stopMove(){
      Roberto.stopMove();
    }

    void Piloto::lookAhead (){
      Roberto.lookAhead();
    }
    
    void Piloto::scanAhead(){
        Roberto.mapAhead();
        obstacle = Roberto.getObstacleInfo();
        
        Serial.print("SCAN AHEAD  | head : ");Serial.println(obstacle->dist[head]);
        Serial.print("SCAN AHEAD  | Obstacle is close? ");Serial.println(obstacle->isClose ? "YES" : "NO");
        
        if(obstacle->isClose)  {
          if(Roberto.shouldTurnRight()){
            Serial.println("SCAN AHEAD  | Right turn");
            Roberto.turnRight();
          }
          else {
            Serial.println("SCAN AHEAD  | Left turn");
            Roberto.turnLeft();
          }
        }
    }

    void Piloto::scanFront(){
        Roberto.mapFront();
        obstacle = Roberto.getObstacleInfo();
        
        Serial.print("SCAN FRONT | head     : ");Serial.println(obstacle->dist[head]);
        Serial.print("SCAN FRONT | diagRight: ");Serial.println(obstacle->dist[diagRight]);
        Serial.print("SCAN FRONT | diagLeft : ");Serial.println(obstacle->dist[diagLeft]);
        Serial.print("SCAN FRONT | Obstacle is close? ");Serial.println(obstacle->isClose ? "YES" : "NO");

        if(obstacle->isClose)  {
          if(Roberto.shouldTurnRight()){
            Serial.println("SCAN FRONT | Right Turn");
            Roberto.turnRight();
          }
          else {
            Serial.println("SCAN FRONT | Left Turn");
            Roberto.turnLeft();
          }
        }
    }

    void Piloto::radarAttach(){
      Roberto.radarAttach();
    }

    struct obstacleMap * Piloto::getObstacleInfo(){
      return Roberto.getObstacleInfo();
  }
    
