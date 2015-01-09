#ifndef PLAYERSTRATEGYINSIDEPLAYMAKER_H
#define PLAYERSTRATEGYINSIDEPLAYMAKER_H

#include "PlayerStrategy.h"

class PlayerStrategyInsidePlaymaker : public PlayerStrategy
{
public:
    PlayerStrategyInsidePlaymaker();
    Heatmap getMap();
    int getValue(int x, int y);
    ProbabilityVector getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYINSIDEPLAYMAKER_H
