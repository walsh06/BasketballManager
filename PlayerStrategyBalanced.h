#ifndef PLAYERSTRATEGYBALANCED_H
#define PLAYERSTRATEGYBALANCED_H

#include "PlayerStrategy.h"

/* Balanced strategy without strong influences
 */
class PlayerStrategyBalanced : public PlayerStrategy
{
public:
    PlayerStrategyBalanced();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYBALANCED_H
