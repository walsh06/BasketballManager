#include "PlayerStrategyScoringForward.h"

PlayerStrategyScoringForward::PlayerStrategyScoringForward():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{1,3,3,3,3,3,3},
                             {1,3,3,9,9,9,9},
                             {1,3,3,9,6,6,6},
                             {1,3,9,9,6,6,6},
                             {1,3,9,9,6,6,6},
                             {1,3,3,9,6,6,6},
                             {1,3,3,9,9,9,9},
                             {1,3,3,3,3,3,3}};

    map.setMap(strategyMap);
}

Heatmap* PlayerStrategyScoringForward::getMap()
{
    return &map;
}

int PlayerStrategyScoringForward::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector* PlayerStrategyScoringForward::getWithBallVector()
{
    return &withBallVector;
}
