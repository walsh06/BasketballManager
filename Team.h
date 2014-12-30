#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "PositionCentre.h"
#include "PositionPointGuard.h"
#include "PositionPowerForward.h"
#include "PositionShootingGuard.h"
#include "PositionSmallForward.h"

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
    int getPressure(int posX, int posY);
    int getPlayersUnderBasket();

    void setTeam(int team);
    void swapSides();

    void restartInbound(int team);
    void setUpFreeThrowOffence(int number);
    void setUpFreeThrowDefence();


    static const int PG = 1, SG = 2, SF = 3, PF = 4, C = 5;
private:

    map<int, Player*> players;
    map<int, int> defenceMatchups;
    int team;
};

#endif // TEAM_H
