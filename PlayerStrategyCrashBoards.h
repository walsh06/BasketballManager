#ifndef PLAYERSTRATEGYCRASHBOARDS_H
#define PLAYERSTRATEGYCRASHBOARDS_H
#include "PlayerStrategy.h"
class PlayerStrategyCrashBoards :  public PlayerStrategy
{
public:
    PlayerStrategyCrashBoards();
    Heatmap getMap();
    int getValue(int x, int y);
    ProbabilityVector getWithBallVector();
    ProbabilityVector withBallVector;

private:
    Heatmap map;
};

#endif // PLAYERSTRATEGYCRASHBOARDS_H
