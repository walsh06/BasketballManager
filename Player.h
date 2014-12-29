#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

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

    void setTeam(int team);
    int getTeam();

    int getRange();

    void movePlayer(int direction);

private:
    int heatMap[8][7];

    int posX, posY;
    int number;
    int team;

    //shooting ratings
    int threeShot, mediumShot, closeShot, dunk, layup;
    //rebound
    int offRebound, defRebound;
    //defence
    int block, steal;
    //offence
    int pass, hands, speed, freethrow;

    void printHeatMap();
    void calcHeatMap();



    const int heatFactor = 3;
};

#endif // PLAYER_H
