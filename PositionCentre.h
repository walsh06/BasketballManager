#ifndef POSITIONCENTRE_H
#define POSITIONCENTRE_H
#include "PlayerPosition.h"
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
