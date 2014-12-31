#include "PlayerStrategyShootThree.h"

PlayerStrategyShootThree::PlayerStrategyShootThree()
{
    int strategyMap[8][7] = {{1,10,10,10,10,10,10},
                             {1,10,5,5,5,5,5},
                             {1,10,5,5,1,1,1},
                             {1,10,5,5,1,1,1},
                             {1,10,5,5,1,1,1},
                             {1,10,5,5,1,1,1},
                             {1,10,5,5,5,5,5},
                             {1,10,10,10,10,10,10}};

    map.setMap(strategyMap);
}

Heatmap PlayerStrategyShootThree::getMap()
{
    return map;
}

int PlayerStrategyShootThree::getValue(int x, int y)
{
    return map.getValue(x, y);
}
