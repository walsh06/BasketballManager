#include "PositionCentre.h"

/** PositionCentre Constructor*/
PositionCentre::PositionCentre()
{
    int posMap[8][7] = {{1,1,1,1,1,1,1},
                     {1,1,3,3,3,3,3},
                     {1,1,3,3,5,5,5},
                     {1,1,3,3,5,5,5},
                     {1,1,3,3,5,5,5},
                     {1,1,3,3,5,5,5},
                     {1,1,3,3,3,3,3},
                     {1,1,1,1,1,1,1}};

    map.setMap(posMap);
}

/** Return the position Heatmap */
Heatmap PositionCentre::getMap()
{
    return map;
}

/** Return influence value of position x, y */
int PositionCentre::getValue(int x, int y)
{
    return map.getValue(x, y);
}
