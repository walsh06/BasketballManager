#include "PositionSmallForward.h"

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

Heatmap PositionSmallForward::getMap()
{
    return map;
}

int PositionSmallForward::getValue(int x, int y)
{
    return map.getValue(x, y);
}
