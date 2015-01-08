#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <string>
#include "Player.h"

class GameView
{
public:
    virtual void updateCommentary(int type, Player *p) = 0;
    virtual void updateTime(int time, int shotClock) = 0;

};
#endif // GAMEVIEW_H
