#include "PositionSmallForward.h"

PositionSmallForward::PositionSmallForward()
{
    int posMap[8][7] = {{2,5,5,5,5,5,5},
                     {2,5,9,9,9,9,9},
                     {2,5,9,9,8,8,8},
                     {2,5,9,9,8,4,4},
                     {2,5,9,9,8,4,4},
                     {2,5,9,9,8,8,8},
                     {2,5,9,9,9,9,9},
                     {2,5,5,5,5,5,5}};

    map.setMap(posMap);
}

Heatmap PositionSmallForward::getMap()
{
    return map;
}

int PositionSmallForward::getValue(int x, int y)
{
    map.getValue(x, y);
}
