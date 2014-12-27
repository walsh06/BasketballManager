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
    Team * teamOne;
    Ball ball;
    void move(Player* p);
    void shoot(Player* p);
    void shootThree(Player* p);
    void shootMedium(Player* p);
    void shootClose(Player* p);

    void rebound();

    void pass(Player* p, Player* teamMate);

    void printCourt();
    void withBall(Player* p, int shotClock);
    int getRandomAction(int arr[], int size, int total);
};

#endif // MATCH_H
