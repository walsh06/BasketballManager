#include "PlayerStrategyInsidePlaymaker.h"

PlayerStrategyInsidePlaymaker::PlayerStrategyInsidePlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,0,5,5,5,5,5})
{
    int strategyMap[8][7] = {{1,3,3,3,3,3,3},
                             {1,3,7,7,7,7,7},
                             {1,3,7,7,8,8,8},
                             {1,3,7,7,8,8,8},
                             {1,3,7,7,8,8,8},
                             {1,3,7,7,8,8,8},
                             {1,3,7,7,7,7,7},
                             {1,3,3,3,3,3,3}};

    map.setMap(strategyMap);
}

Heatmap PlayerStrategyInsidePlaymaker::getMap()
{
    return map;
}

int PlayerStrategyInsidePlaymaker::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector PlayerStrategyInsidePlaymaker::getWithBallVector()
{
    return withBallVector;
}
