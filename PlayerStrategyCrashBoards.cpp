#include "PlayerStrategyCrashBoards.h"


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

Heatmap PlayerStrategyCrashBoards::getMap()
{
    return map;
}

int PlayerStrategyCrashBoards::getValue(int x, int y)
{
    return map.getValue(x, y);
}

ProbabilityVector PlayerStrategyCrashBoards::getWithBallVector()
{
    return withBallVector;
}
