#ifndef PLAYERSTRATEGYINSIDEPLAYMAKER_H
#define PLAYERSTRATEGYINSIDEPLAYMAKER_H

#include "PlayerStrategy.h"

/* Strategy for a playmaker who takes shots closer to the basket */
class PlayerStrategyInsidePlaymaker : public PlayerStrategy
{
public:
    PlayerStrategyInsidePlaymaker();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYINSIDEPLAYMAKER_H
