#ifndef TESTGAMEVIEW_H
#define TESTGAMEVIEW_H

#include "GameView.h"

class TestGameView : public GameView
{
public:
    TestGameView();
    void updateCommentary(int type, Player *p);
    void printValue(std::string valueName, int value);
    void updateTime(int time, int shotClock);
};

#endif // TESTGAMEVIEW_H
