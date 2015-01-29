#include "PlayerStrategyInsidePlaymaker.h"

PlayerStrategyInsidePlaymaker::PlayerStrategyInsidePlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,4,4,4,4,4,10})
{
    int strategyMap[9][7] = {{1,-5,-5,-5,-5,-5,-5},
                             {1,-5,-5,9,9,9,9},
                             {1,-5,-5,9,7,7,7},
                             {1,-5,9,9,7,4,4},
                             {1,-5,9,9,7,4,4},
                             {1,-5,-5,9,7,7,7},
                             {1,-5,-5,9,9,9,9},
                             {1,-5,-5,-5,-5,-5,-5}};

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
