#include "PlayerStrategyInsideOutside.h"

PlayerStrategyInsideOutside::PlayerStrategyInsideOutside():withBallVector({0,0,0,0,0,0,0,0,0,3,0,0,0,0,5})
{
    int strategyMap[8][7] = {{1,8,8,8,8,8,8},
                             {1,8,6,2,2,2,2},
                             {1,8,6,2,8,8,8},
                             {1,8,2,4,8,8,8},
                             {1,8,2,4,8,8,8},
                             {1,8,6,2,8,8,8},
                             {1,8,6,2,2,2,2},
                             {1,8,8,8,8,8,8}};

    map.setMap(strategyMap);
}

Heatmap PlayerStrategyInsideOutside::getMap()
{
    return map;
}

int PlayerStrategyInsideOutside::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector PlayerStrategyInsideOutside::getWithBallVector()
{
    return withBallVector;
}
