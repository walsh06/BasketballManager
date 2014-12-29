#include "PositionPointGuard.h"

PositionPointGuard::PositionPointGuard()
{
    int posMap[8][7] = {{5,10,10,10,10,10,10},
                     {5,10,8,6,6,6,6},
                     {5,10,8,5,3,3,3},
                     {5,10,8,5,3,2,2},
                     {5,10,8,5,3,2,2},
                     {5,10,8,5,3,3,3},
                     {5,10,8,6,6,6,6},
                     {5,10,10,10,10,10,10}};

    map.setMap(posMap);
}

Heatmap PositionPointGuard::getMap()
{
    return map;
}

int PositionPointGuard::getValue(int x, int y)
{
    map.getValue(x, y);
}
