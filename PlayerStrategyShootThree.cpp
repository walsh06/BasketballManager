#include "PlayerStrategyShootThree.h"

PlayerStrategyShootThree::PlayerStrategyShootThree():withBallVector({0,0,0,0,0,0,0,0,0,4,0,0,0,0,0})
{
    int strategyMap[8][7] = {{1,8,8,8,8,8,8},
                             {1,8,8,4,4,4,4},
                             {1,8,8,4,1,1,1},
                             {1,8,4,4,1,1,1},
                             {1,8,4,4,1,1,1},
                             {1,8,8,4,1,1,1},
                             {1,8,8,4,4,4,4},
                             {1,8,8,8,8,8,8}};

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
