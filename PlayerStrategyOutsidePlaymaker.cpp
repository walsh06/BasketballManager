#include "PlayerStrategyOutsidePlaymaker.h"

/** PlayerStrategyOutsidePlaymaker Constructor */
PlayerStrategyOutsidePlaymaker::PlayerStrategyOutsidePlaymaker():withBallVector({0,0,0,0,0,0,0,0,0,0,5,5,5,5,0})
{
    int strategyMap[8][7] = {{1,8,8,8,8,8,8},
                             {1,8,8,6,6,6,6},
                             {1,8,8,3,2,2,2},
                             {1,8,6,3,2,1,1},
                             {1,8,6,3,2,1,1},
                             {1,8,8,3,2,2,2},
                             {1,8,8,6,6,6,6},
                             {1,8,8,8,8,8,8}};

    map.setMap(strategyMap);
}

/** Return the heatmap */
Heatmap* PlayerStrategyOutsidePlaymaker::getMap()
{
    return &map;
}

/** Return the influence value at position x, y */
int PlayerStrategyOutsidePlaymaker::getValue(int x, int y)
{
    return map.getValue(x, y);
}

/** Return the probability vector of the strategy */
ProbabilityVector* PlayerStrategyOutsidePlaymaker::getWithBallVector()
{
    return &withBallVector;
}
