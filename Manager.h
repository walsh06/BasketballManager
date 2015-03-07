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
    void pickStartingPosition(int pos, map<int, Player *> &players);
    void pickStartingPositionAdvanced(int pos, map<int, Player *> &players);
    void subPlayer(int pos, map<int, Player*> &players);
    void subPlayerAdvanced(int pos, map<int, Player *> &players, int time, int quarter);

    void printRatings();

private:
    vector<vector<float>> playerRatings;
    int playerCount;
    int energyThresholdSubOut, energyThresholdSubIn, subOutThreshold;

    int getBestPlayerForPosition(map<int, Player *> players, int start, int end);
    float calculateMinutes(int index);
};

#endif // MANAGER_H
