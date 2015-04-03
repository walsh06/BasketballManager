#ifndef PLAYERSTRATEGYSHOOTTHREE_H
#define PLAYERSTRATEGYSHOOTTHREE_H
#include "PlayerStrategy.h"

/* Strategy for a player who takes a lot of three point shots */
class PlayerStrategyShootThree : public PlayerStrategy
{
public:
    PlayerStrategyShootThree();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;

};

#endif // PLAYERSTRATEGYSHOOTTHREE_H
