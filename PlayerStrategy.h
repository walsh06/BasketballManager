#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include <Heatmap.h>

class PlayerStrategy
{
public:
    virtual Heatmap getMap() = 0;
    virtual int getValue(int x, int y) = 0;
};
#endif // PLAYERSTRATEGY_H
