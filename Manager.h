#ifndef MANAGER_H
#define MANAGER_H
#include "Player.h"

#include <iostream>

using namespace std;
class Manager
{
public:
    Manager();
    void evaluatePlayers(map<int, Player*> players);
    int getBestStrategyForPlayer(int playerPos);
    int getBestPlayerForStrategy(int strategy);
    void subPlayer(int pos, map<int, Player*> &players);

    void printRatings();

private:
    vector<vector<float>> playerRatings;
    int playerCount;
    int energyThresholdSubOut, energyThresholdSubIn;
};

#endif // MANAGER_H
