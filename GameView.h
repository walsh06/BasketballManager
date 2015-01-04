#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <string>

class GameView
{
public:
    virtual void updateCommentary(int type, std::string nameOne) = 0;
};
#endif // GAMEVIEW_H
