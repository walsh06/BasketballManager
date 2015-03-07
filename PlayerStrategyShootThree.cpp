#include "PlayerStrategyShootThree.h"

PlayerStrategyShootThree::PlayerStrategyShootThree():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{1,7,7,7,7,7,7},
                             {1,7,7,3,3,3,3},
                             {1,7,7,3,1,1,1},
                             {1,7,3,3,1,1,1},
                             {1,7,3,3,1,1,1},
                             {1,7,7,3,1,1,1},
                             {1,7,7,3,3,3,3},
                             {1,7,7,7,7,7,7}};

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
