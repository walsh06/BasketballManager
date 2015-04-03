#include "PositionShootingGuard.h"

/** PositionCentre Constructor*/
PositionShootingGuard::PositionShootingGuard()
{
    int posMap[8][7] = {{2,3,3,3,3,3,3},
                     {2,3,3,5,5,5,5},
                     {2,3,3,5,2,2,2},
                     {2,3,5,3,2,1,1},
                     {2,3,5,5,2,1,1},
                     {2,3,3,5,2,2,2},
                     {2,3,3,5,5,5,5},
                     {2,3,3,3,3,3,3}};

    map.setMap(posMap);
}

/** Return the position Heatmap */
Heatmap PositionShootingGuard::getMap()
{
    return map;
}

/** Return influence value of position x, y */
int PositionShootingGuard::getValue(int x, int y)
{
    return map.getValue(x, y);
}

