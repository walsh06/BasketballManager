#include "PositionPowerForward.h"

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

Heatmap PositionPowerForward::getMap()
{
    return map;
}

int PositionPowerForward::getValue(int x, int y)
{
    return map.getValue(x, y);
}
