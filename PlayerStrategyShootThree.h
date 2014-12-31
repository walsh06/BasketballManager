#ifndef PLAYERSTRATEGYSHOOTTHREE_H
#define PLAYERSTRATEGYSHOOTTHREE_H
#include "PlayerStrategy.h"

class PlayerStrategyShootThree : public PlayerStrategy
{
public:
    PlayerStrategyShootThree();
    Heatmap getMap();
    int getValue(int x, int y);

private:
    Heatmap map;

};

#endif // PLAYERSTRATEGYSHOOTTHREE_H
