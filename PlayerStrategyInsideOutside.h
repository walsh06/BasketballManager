#ifndef PLAYERSTRATEGYINSIDEOUTSIDE_H
#define PLAYERSTRATEGYINSIDEOUTSIDE_H
#include "PlayerStrategy.h"

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
