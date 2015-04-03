#ifndef POSITIONPOWERFORWARD_H
#define POSITIONPOWERFORWARD_H
#include "PlayerPosition.h"

/* Position Class for a Power Forward */
class PositionPowerForward : public PlayerPosition
{
public:
    PositionPowerForward();
    Heatmap getMap();
    int getValue(int x, int y);

private:
    Heatmap map;
};

#endif // POSITIONPOWERFORWARD_H
