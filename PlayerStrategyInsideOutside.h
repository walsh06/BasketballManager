#ifndef PLAYERSTRATEGYINSIDEOUTSIDE_H
#define PLAYERSTRATEGYINSIDEOUTSIDE_H
#include "PlayerStrategy.h"

/* Strategy for a player who takes even inside and outside shots */
class PlayerStrategyInsideOutside : public PlayerStrategy
{
public:
    PlayerStrategyInsideOutside();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYINSIDEOUTSIDE_H
