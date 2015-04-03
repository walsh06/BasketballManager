#include "PlayerStrategyBalancedPlaymaker.h"

/** PlayerStrategyBalancedPlaymaker Constructor */
PlayerStrategyBalancedPlaymaker::PlayerStrategyBalancedPlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,0,8,8,8,8,0})
{
    int strategyMap[8][7] = {{1,6,6,6,6,6,6},
                             {1,6,6,6,6,6,6},
                             {1,6,6,4,2,2,2},
                             {1,6,6,4,2,2,2},
                             {1,6,6,4,2,2,2},
                             {1,6,6,4,2,2,2},
                             {1,6,6,6,6,6,6},
                             {1,6,6,6,6,6,6}};

    map.setMap(strategyMap);
}

/** Return the heatmap */
Heatmap* PlayerStrategyBalancedPlaymaker::getMap()
{
    return &map;
}

/** Return the influence value at position x, y */
int PlayerStrategyBalancedPlaymaker::getValue(int x, int y)
{
    return map.getValue(x, y);
}

/** Return the probability vector of the strategy */
ProbabilityVector* PlayerStrategyBalancedPlaymaker::getWithBallVector()
{
    return &withBallVector;
}
