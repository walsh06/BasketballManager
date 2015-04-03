#include "PositionSmallForward.h"

/** PositionCentre Constructor*/
PositionSmallForward::PositionSmallForward()
{
    int posMap[8][7] = {{1,2,2,2,2,2,2},
                     {1,2,2,5,5,5,5},
                     {1,2,2,5,4,4,4},
                     {1,2,5,5,4,2,2},
                     {1,2,5,5,4,2,2},
                     {1,2,2,5,4,4,4},
                     {1,2,2,5,5,5,5},
                     {1,2,2,2,2,2,2}};

    map.setMap(posMap);
}

/** Return the position Heatmap */
Heatmap PositionSmallForward::getMap()
{
    return map;
}

/** Return influence value of position x, y */
int PositionSmallForward::getValue(int x, int y)
{
    return map.getValue(x, y);
}

