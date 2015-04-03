#ifndef COMMENTARY_H
#define COMMENTARY_H
#include <map>
#include <vector>
#include "Player.h"
#include "pugixml.hpp"

/* Commentary takes care of commentary generation during a simulation. The MatchScreen will
 * have an instance of commentary and make calls to get updated commentary phrases. These get
 * displayed on screen then
 */
class Commentary
{
public:
    Commentary();
    std::string getCommentary(int eventType, Player *p, Player *p2 = NULL );
private:
    std::map<int, std::vector<std::string> > comments;
    std::vector<std::string> adjectives;
    std::map<int, std::vector<std::tuple<int, std::string>>> analysis;

    void readXML();
};

#endif // COMMENTARY_H
