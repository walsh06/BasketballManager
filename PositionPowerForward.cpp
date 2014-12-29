#include "PositionPowerForward.h"

PositionPowerForward::PositionPowerForward()
{
    int posMap[8][7] = {{1,3,3,3,3,3,3},
                     {1,3,6,6,6,6,6},
                     {1,3,6,7,10,10,10},
                     {1,3,6,7,10,8,8},
                     {1,3,6,7,10,8,8},
                     {1,3,6,7,10,10,10},
                     {1,3,6,6,6,6,6},
                     {1,3,3,3,3,3,3}};
    map.setMap(posMap);
}

Heatmap PositionPowerForward::getMap()
{
    return map;
}

int PositionPowerForward::getValue(int x, int y)
{
    map.getValue(x, y);
}
