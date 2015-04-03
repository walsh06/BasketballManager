#ifndef PLAYERSTRATEGYPOSTSCORER_H
#define PLAYERSTRATEGYPOSTSCORER_H

#include "PlayerStrategy.h"

/*Strategy for a player who shoots a lot in the post and gets rebounds */
class PlayerStrategyPostScorer : public PlayerStrategy
{
public:
    PlayerStrategyPostScorer();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYPOSTSCORER_H
