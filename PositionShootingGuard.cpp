#include "PositionShootingGuard.h"

PositionShootingGuard::PositionShootingGuard()
{
    int posMap[8][7] = {{5,9,9,9,9,9,9},
                     {5,9,9,9,9,9,5},
                     {5,9,9,6,3,3,3},
                     {5,9,9,6,3,2,2},
                     {5,9,9,6,3,2,2},
                     {5,9,9,6,3,3,3},
                     {5,9,9,9,9,9,9},
                     {5,9,9,9,9,9,9}};

    map.setMap(posMap);
}

Heatmap PositionShootingGuard::getMap()
{
    return map;
}

int PositionShootingGuard::getValue(int x, int y)
{
    return map.getValue(x, y);
}
