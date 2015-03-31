#ifndef PLAYERPOSITION_H
#define PLAYERPOSITION_H

/* Interface implemented by player position classes
 */
#include "Heatmap.h"
class PlayerPosition
{
public:
    virtual Heatmap getMap() = 0;
    virtual int getValue(int x, int y) = 0;
};
#endif // PLAYERPOSITION_H
