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
    Team * teamOne, *teamTwo;
    Team teams[2];
    int shotClock, time;
    Ball ball;
    vector<Player*> orderOfPlay;


    void move(Player* p);
    void withBall(Player* p, int shotClock);

    void shoot(Player* p);
    void shootThree(Player* p);
    void shootMedium(Player* p);
    void shootClose(Player* p);
    void pass(Player* p, Player* teamMate);
    void rebound();

    void moveDefence(Player* p);
    void moveDefenceLoose(Player *p, Player opposition);
    void moveDefenceTight(Player* p, Player opposition);

    void printCourt();
    void setOrderOfPlay();
    int getRandomAction(int arr[], int size, int total);
};

#endif // MATCH_H
