#ifndef MATCH_H
#define MATCH_H

#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "ProbabilityVector.h"
#include "Heatmap.h"

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <tuple>

using namespace std;

class Match
{
public:
    Match();
    ~Match();

    void sim();
    void writeMatchStats(string filename);
private:
    int firstPossession;
    Heatmap shotMap;
    int gameState;
    const int INPLAY = 0, INBOUND = 1;
    Team * teamOne, *teamTwo;
    Team *teams[2];
    int shotClock, time;
    Ball ball;
    vector<Player*> orderOfPlay;
    tuple<Player *, int> assist;
    int score[2];


    void move(Player* p);
    void withBall(Player* p, int shotClock);
    void driveBasket(Player *p);

    void shoot(Player* p, int pressure);
    void shootUnderBasket(Player *p, int pressure);
    void shootThree(Player* p, int pressure);
    void shootMedium(Player* p, int pressure);
    void shootClose(Player* p, int pressure);
    void shootFreeThrow(Player* p, int numOfFreethrows);

    void pass(Player* p, Player* teamMate);
    void passInbound(Player* p);
    void rebound();
    void checkAssist();

    void moveDefence(Player* p);
    void moveDefenceLoose(Player *p, Player opposition);
    void moveDefenceTight(Player* p, Player opposition);

    void block(Player *p);
    void steal(Player *p, Player opposition);

    void printCourt();

    int getScoreDifference(int team);
    void jumpBall();
    void setOrderOfPlay();
    int getOtherTeam(int team);
    void swapSides(int playerNum);
    void setUpRestartInbound();
};

#endif // MATCH_H
