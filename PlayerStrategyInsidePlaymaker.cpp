#include "PlayerStrategyInsidePlaymaker.h"

PlayerStrategyInsidePlaymaker::PlayerStrategyInsidePlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,4,4,4,4,4,10})
{
    int strategyMap[8][7] = {{1,1,1,1,1,1,1},
                             {1,1,1,9,9,9,9},
                             {1,1,1,9,7,7,7},
                             {1,1,9,9,7,4,4},
                             {1,1,9,9,7,4,4},
                             {1,1,1,9,7,7,7},
                             {1,1,1,9,9,9,9},
                             {1,1,1,1,1,1,1}};

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
