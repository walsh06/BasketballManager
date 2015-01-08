#ifndef CONSOLEGAMEVIEW_H
#define CONSOLEGAMEVIEW_H

#include "GameView.h"
#include "pugixml.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

class ConsoleGameView : public GameView
{
public:
    ConsoleGameView();

    void updateCommentary(int type, Player *p);
    void printValue(std::string valueName, int value);
    void updateTime(int time, int shotClock);

private:
    std::map<int, std::vector<std::string> > comments;
    std::string createCommentary(std::string comment, const std::string name);

    void readXML();
};

#endif // CONSOLEGAMEVIEW_H
