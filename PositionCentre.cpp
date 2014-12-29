#include "PositionCentre.h"


PositionCentre::PositionCentre()
{
    int posMap[8][7] = {{1,2,2,2,2,2,2},
                     {1,2,5,5,5,2,1},
                     {1,2,5,5,10,10,10},
                     {1,2,5,5,10,10,10},
                     {1,2,5,5,10,10,10},
                     {1,2,5,5,10,10,10},
                     {1,2,5,5,5,2,1},
                     {1,2,2,2,2,2,2}};

    map.setMap(posMap);
}

Heatmap PositionCentre::getMap()
{
    return map;
}

int PositionCentre::getValue(int x, int y)
{
    map.getValue(x, y);
}
