#include "PlayerStrategyInsideOutside.h"

/** PlayerStrategyInsideOutside Constructor */
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
