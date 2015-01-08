#include "PositionCentre.h"


PositionCentre::PositionCentre()
{
    int posMap[8][7] = {{1,1,1,1,1,1,1},
                     {1,1,5,5,5,5,5},
                     {1,1,5,5,10,10,10},
                     {1,1,5,5,10,10,10},
                     {1,1,5,5,10,10,10},
                     {1,1,5,5,10,10,10},
                     {1,1,5,5,5,5,5},
                     {1,1,1,1,1,1,1}};

    map.setMap(posMap);
}

Heatmap PositionCentre::getMap()
{
    return map;
}

int PositionCentre::getValue(int x, int y)
{
    return map.getValue(x, y);
}
