#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include <vector>
#include <map>

using namespace std;

class Team
{
public:
    Team();
    Player* getPlayer(int position);
    vector<Player*> getOtherPlayers(int number);
    int getPlayerPosition(int number);
    int getMatchup(int position);
    int getMatchup(Player p);
    void setTeam(int team);

    static const int PG = 1, SG = 2, SF = 3, PF = 4, C = 5;
private:

    map<int, Player*> players;
    map<int, int> defenceMatchups;
    int team;
};

#endif // TEAM_H
