#include "PlayerStrategyOutsidePlaymaker.h"


PlayerStrategyOutsidePlaymaker::PlayerStrategyOutsidePlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,5,5,5,5,5,0})
{
    int strategyMap[8][7] = {{1,9,9,9,9,9,9},
                             {1,9,6,6,6,6,6},
                             {1,9,6,3,2,2,2},
                             {1,9,6,3,2,1,1},
                             {1,9,6,3,2,1,1},
                             {1,9,6,3,2,2,2},
                             {1,9,6,6,6,6,6},
                             {1,9,9,9,9,9,9}};

    map.setMap(strategyMap);
}

Heatmap PlayerStrategyOutsidePlaymaker::getMap()
{
    return map;
}

int PlayerStrategyOutsidePlaymaker::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector PlayerStrategyOutsidePlaymaker::getWithBallVector()
{
    return withBallVector;
}
