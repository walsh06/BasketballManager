#include "PositionSmallForward.h"

PositionSmallForward::PositionSmallForward()
{
    int posMap[8][7] = {{1,3,3,3,3,3,3},
                     {1,3,3,4,4,4,4},
                     {1,3,3,4,4,4,4},
                     {1,3,4,4,4,2,2},
                     {1,3,4,4,4,2,2},
                     {1,3,3,4,4,4,4},
                     {1,3,3,4,4,4,4},
                     {1,3,3,3,3,3,3}};

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
