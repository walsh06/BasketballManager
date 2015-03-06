#ifndef COMMENTARY_H
#define COMMENTARY_H
#include <map>
#include <vector>
#include "Player.h"
#include "pugixml.hpp"
class Commentary
{
public:
    Commentary();
    std::string getCommentary(int eventType, Player *p, Player *p2 = NULL );
private:
    std::map<int, std::vector<std::string> > comments;
    std::vector<std::string> adjectives;
    void readXML();
};

#endif // COMMENTARY_H
