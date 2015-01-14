#ifndef PLAYERSTRATEGYPOSTSCORER_H
#define PLAYERSTRATEGYPOSTSCORER_H

#include "PlayerStrategy.h"

class PlayerStrategyPostScorer : public PlayerStrategy
{
public:
    PlayerStrategyPostScorer();
    Heatmap getMap();
    int getValue(int x, int y);
    ProbabilityVector getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYPOSTSCORER_H
