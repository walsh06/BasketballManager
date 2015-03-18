#include "PlayerStrategyDynamic.h"


PlayerStrategyDynamic::PlayerStrategyDynamic():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0}};

    map.setMap(strategyMap);
}

Heatmap* PlayerStrategyDynamic::getMap()
{
    return &map;
}

int PlayerStrategyDynamic::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector* PlayerStrategyDynamic::getWithBallVector()
{
    return &withBallVector;
}
