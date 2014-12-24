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
    int setPos(int x, int y);
    int getNumber();
    int getThreeShot();
    int getMediumShot();
    int getCloseShot();
    int getDunk();
    int getLayup();
    int getOffRebound();
    int getDefRebound();
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
    int pass, hands;

    void printHeatMap();
    void calcHeatMap();



    const int heatFactor = 2;
};

#endif // PLAYER_H
