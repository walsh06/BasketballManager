#ifndef POSITIONCENTRE_H
#define POSITIONCENTRE_H
#include "PlayerPosition.h"

/* Position Class for a Centre */
class PositionCentre : public PlayerPosition
{
public:
    PositionCentre();
    Heatmap getMap();
    int getValue(int x, int y);

private:
    Heatmap map;
};

#endif // POSITIONCENTRE_H
