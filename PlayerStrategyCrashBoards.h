#ifndef PLAYERSTRATEGYCRASHBOARDS_H
#define PLAYERSTRATEGYCRASHBOARDS_H
#include "PlayerStrategy.h"

/* Strategy for a player who gets a lot of rebounds */
class PlayerStrategyCrashBoards :  public PlayerStrategy
{
public:
    PlayerStrategyCrashBoards();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYCRASHBOARDS_H
