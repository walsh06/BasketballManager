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
    Player* getPlayer(int numbers);
    vector<Player*> getOtherPlayers(int number);

    void setTeam(int team);
private:
    map<int, Player*> players;
    int team;
};

#endif // TEAM_H
