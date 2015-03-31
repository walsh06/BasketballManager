#include "PlayerStrategyBalanced.h"

/** PlayerStrategyBalanced Constructor */
PlayerStrategyBalanced::PlayerStrategyBalanced():withBallVector({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0})
{
    int strategyMap[8][7] = {{1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5},
                             {1,5,5,5,5,5,5}};

    map.setMap(strategyMap);
}

/** Return the heatmap */
Heatmap* PlayerStrategyBalanced::getMap()
{
    return &map;
}

/** Return the influence value at position x, y */
int PlayerStrategyBalanced::getValue(int x, int y)
{
    return map.getValue(x, y);
}

/** Return the probability vector of the strategy */
ProbabilityVector* PlayerStrategyBalanced::getWithBallVector()
{
    return &withBallVector;
}
