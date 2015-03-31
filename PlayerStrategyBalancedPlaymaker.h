#ifndef PLAYERSTRATEGYBALANCEDPLAYMAKER_H
#define PLAYERSTRATEGYBALANCEDPLAYMAKER_H

#include "PlayerStrategy.h"

/* Strategy for a playmaker who takes even outside/inside shots */
class PlayerStrategyBalancedPlaymaker : public PlayerStrategy
{
public:
    PlayerStrategyBalancedPlaymaker();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYBALANCEDPLAYMAKER_H
