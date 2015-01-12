#include "PositionShootingGuard.h"

PositionShootingGuard::PositionShootingGuard()
{
    int posMap[8][7] = {{2,4,4,4,4,4,4},
                     {2,4,4,4,4,4,4},
                     {2,4,4,3,2,2,2},
                     {2,4,4,3,2,1,1},
                     {2,4,4,3,2,1,1},
                     {2,4,4,3,2,2,2},
                     {2,4,4,4,4,4,4},
                     {2,4,4,4,4,4,4}};

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
