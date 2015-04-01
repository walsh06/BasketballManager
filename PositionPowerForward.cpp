#include "PositionPowerForward.h"

/** PositionCentre Constructor*/
PositionPowerForward::PositionPowerForward()
{
    int posMap[8][7] = {{1,2,2,2,2,2,2},
                     {1,2,3,3,3,3,3},
                     {1,2,3,3,5,5,5},
                     {1,2,3,3,5,4,4},
                     {1,2,3,3,5,4,4},
                     {1,2,3,3,5,5,5},
                     {1,2,3,3,3,3,3},
                     {1,2,2,2,2,2,2}};
    map.setMap(posMap);
}

/** Return the position Heatmap */
Heatmap PositionPowerForward::getMap()
{
    return map;
}

/** Return influence value of position x, y */
int PositionPowerForward::getValue(int x, int y)
{
    return map.getValue(x, y);
}
