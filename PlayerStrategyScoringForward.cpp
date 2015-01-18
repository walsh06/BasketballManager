#include "PlayerStrategyScoringForward.h"

PlayerStrategyScoringForward::PlayerStrategyScoringForward():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{1,4,4,4,4,4,4},
                             {1,4,4,8,8,8,8},
                             {1,4,4,8,6,6,6},
                             {1,4,8,8,6,6,6},
                             {1,4,8,8,6,6,6},
                             {1,4,4,8,6,6,6},
                             {1,4,4,8,8,8,8},
                             {1,4,4,4,4,4,4}};

    map.setMap(strategyMap);
}

Heatmap PlayerStrategyScoringForward::getMap()
{
    return map;
}

int PlayerStrategyScoringForward::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector PlayerStrategyScoringForward::getWithBallVector()
{
    return withBallVector;
}
