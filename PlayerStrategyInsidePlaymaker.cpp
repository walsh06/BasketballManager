#include "PlayerStrategyInsidePlaymaker.h"

PlayerStrategyInsidePlaymaker::PlayerStrategyInsidePlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,2,4,4,4,4,6})
{
    int strategyMap[9][7] = {{1,2,2,2,2,2,2},
                             {1,2,2,9,9,9,9},
                             {1,2,2,9,7,7,7},
                             {1,2,9,9,7,4,4},
                             {1,2,9,9,7,4,4},
                             {1,2,2,9,7,7,7},
                             {1,2,2,9,9,9,9},
                             {1,2,2,2,2,2,2}};

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
