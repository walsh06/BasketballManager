#ifndef POSITIONPOINTGUARD_H
#define POSITIONPOINTGUARD_H

#include "PlayerPosition.h"

/* Position Class for a Point Guard */
class PositionPointGuard : public PlayerPosition
{
public:
    PositionPointGuard();
    Heatmap getMap();
    int getValue(int x, int y);

private:
    Heatmap map;
};

#endif // POSITIONPOINTGUARD_H
