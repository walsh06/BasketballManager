#include "PlayerStrategyInsidePlaymaker.h"

/** PlayerStrategyInsidePlaymaker Constructor */
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
