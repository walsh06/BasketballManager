#ifndef PLAYERSTRATEGYOUTSIDEPLAYMAKER_H
#define PLAYERSTRATEGYOUTSIDEPLAYMAKER_H

#include "PlayerStrategy.h"

/* Strategy for a playmake who takes a lot more three point shots */
class PlayerStrategyOutsidePlaymaker : public PlayerStrategy
{
public:
    PlayerStrategyOutsidePlaymaker();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYOUTSIDEPLAYMAKER_H
