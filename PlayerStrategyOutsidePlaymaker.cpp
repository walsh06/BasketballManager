#include "PlayerStrategyOutsidePlaymaker.h"


PlayerStrategyOutsidePlaymaker::PlayerStrategyOutsidePlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,0,5,5,5,5,0})
{
    int strategyMap[8][7] = {{1,8,8,8,8,8,8},
                             {1,8,8,6,6,6,6},
                             {1,8,8,3,2,2,2},
                             {1,8,6,3,2,1,1},
                             {1,8,6,3,2,1,1},
                             {1,8,8,3,2,2,2},
                             {1,8,8,6,6,6,6},
                             {1,8,8,8,8,8,8}};

    map.setMap(strategyMap);
}

Heatmap* PlayerStrategyOutsidePlaymaker::getMap()
{
    return &map;
}

int PlayerStrategyOutsidePlaymaker::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector* PlayerStrategyOutsidePlaymaker::getWithBallVector()
{
    return &withBallVector;
}
