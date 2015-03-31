#include "PlayerStrategyShootThree.h"

/** PlayerStrategyShootThree Constructor */
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
