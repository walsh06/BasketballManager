#ifndef POSITIONSMALLFORWARD_H
#define POSITIONSMALLFORWARD_H
#include "PlayerPosition.h"

/* Position Class for a Small Forward */
class PositionSmallForward : public PlayerPosition
{
public:
    PositionSmallForward();
    Heatmap getMap();
    int getValue(int x, int y);

private:
    Heatmap map;
};

#endif // POSITIONSMALLFORWARD_H
