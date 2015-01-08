#ifndef PLAYER_H
#define PLAYER_H

#include "Heatmap.h"
#include "PlayerPosition.h"
#include "PlayerStrategy.h"
#include <string>
using namespace std;

class Player
{
public:
    Player(int number);

    int getPosValue(int x, int y);
    int getPosValue();
    int getPosX();
    int getPosY();
    void setPos(int x, int y);
    void setRandomPos();
    void setPlayingPosition(PlayerPosition *pos);
    void setStrategy(PlayerStrategy *strategy);
    void updateMap();


    int getNumber();
    int getThreeShot();
    int getMediumShot();
    int getCloseShot();
    int getDunk();
    int getLayup();
    int getUnderBasketShot();
    int getOffRebound();
    int getDefRebound();
    int getFreethrow();
    int getBlock();
    int getSpeed();
    int getSteal();
    int getPass();
    string getName();

    void setTeam(int team);
    int getTeam();

    int getRange();

    void movePlayer(int direction);

    Heatmap moveTrackerMap;
private:
    Heatmap posValueMap, finalMap ;
    PlayerPosition *position;
    PlayerStrategy *strategy;

    int posX, posY;
    int number;
    int team;
    string name;

    //shooting ratings
    int threeShot, mediumShot, closeShot, dunk, layup;
    //rebound
    int offRebound, defRebound;
    //defence
    int block, steal;
    //offence
    int pass, hands, speed, freethrow;

    void calcHeatMap();




    const int heatFactor = 3;
};

#endif // PLAYER_H
