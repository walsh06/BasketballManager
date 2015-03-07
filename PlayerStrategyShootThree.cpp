#include "PlayerStrategyShootThree.h"

PlayerStrategyShootThree::PlayerStrategyShootThree():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{1,9,9,9,9,9,9},
                             {1,9,9,3,3,3,3},
                             {1,9,9,3,1,1,1},
                             {1,9,3,3,1,1,1},
                             {1,9,3,3,1,1,1},
                             {1,9,9,3,1,1,1},
                             {1,9,9,3,3,3,3},
                             {1,9,9,9,9,9,9}};

    map.setMap(strategyMap);
}

Heatmap PlayerStrategyShootThree::getMap()
{
    return map;
}

int PlayerStrategyShootThree::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector PlayerStrategyShootThree::getWithBallVector()
{
    return withBallVector;
}
