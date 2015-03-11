#include "PlayerStrategyBalanced.h"


PlayerStrategyBalanced::PlayerStrategyBalanced():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5}};

    map.setMap(strategyMap);
}

Heatmap* PlayerStrategyBalanced::getMap()
{
    return &map;
}

int PlayerStrategyBalanced::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector* PlayerStrategyBalanced::getWithBallVector()
{
    return &withBallVector;
}
