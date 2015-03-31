#include "PlayerStrategyCrashBoards.h"

/** PlayerStrategyCrashBoards Constructor */
PlayerStrategyCrashBoards::PlayerStrategyCrashBoards():withBallVector({0,0,3,0,0,3,0,0,3,-3,3,3,3,3,0})
{
    int strategyMap[8][7] = {{1,1,1,1,1,1,1},
                             {1,1,2,2,2,2,2},
                             {1,1,2,2,6,6,6},
                             {1,1,2,2,6,6,6},
                             {1,1,2,2,6,6,6},
                             {1,1,2,2,6,6,6},
                             {1,1,2,2,2,2,2},
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
