#ifndef MATCH_H
#define MATCH_H

#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "ProbabilityVector.h"

#include <iostream>

#include <time.h>
#include <stdlib.h>

using namespace std;

class Match
{
public:
    Match();
    void sim();
private:
    int gameState;
    const int INPLAY = 0, INBOUND = 1;
    Team * teamOne, *teamTwo;
    Team *teams[2];
    int shotClock, time;
    Ball ball;
    vector<Player*> orderOfPlay;
    int score[2];


    void move(Player* p);
    void withBall(Player* p, int shotClock);

    void shoot(Player* p);
    void shootUnderBasket(Player *p);
    void shootThree(Player* p);
    void shootMedium(Player* p);
    void shootClose(Player* p);
    void shootFreeThrow(Player* p, int numOfFreethrows);

    void pass(Player* p, Player* teamMate);
    void passInbound(Player* p);
    void rebound();

    void moveDefence(Player* p);
    void moveDefenceLoose(Player *p, Player opposition);
    void moveDefenceTight(Player* p, Player opposition);

    void block(Player *p);

    void printCourt();
    void setOrderOfPlay();
    int getOtherTeam(int team);
    void swapSides();
    void setUpRestartInbound();

};

#endif // MATCH_H
