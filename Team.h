#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "PositionCentre.h"
#include "PositionPointGuard.h"
#include "PositionPowerForward.h"
#include "PositionShootingGuard.h"
#include "PositionSmallForward.h"
#include "PlayerStrategyCrashBoards.h"
#include "PlayerStrategyShootThree.h"
#include "PlayerStrategyInsideOutside.h"
#include "PlayerStrategyOutsidePlaymaker.h"
#include "PlayerStrategyInsidePlaymaker.h"
#include "PlayerStrategyPostScorer.h"
#include "PlayerStrategyBalanced.h"
#include "PlayerStrategyBalancedPlaymaker.h"

#include "pugixml.hpp"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Team
{
public:
    Team(string teamName);
    Player* getPlayer(int position);
    vector<Player*> getOtherPlayers(int number);
    void swapPlayers(int indexOne, int indexTwo);
    int getPlayerPosition(int number);
    int getMatchup(int position);
    int getMatchup(Player p);
    int getPressure(int posX, int posY);
    int getPlayersUnderBasket();
    vector<int> getPlayersInPosition(int posX, int posY);
    int getDefenceSetting(int pos);


    void setTeam(int team);
    void updatePosition(int index, int strategy);
    void updateStrategy(int index, int position);
    void swapSides();

    void restartInbound(int team);
    void offensiveInbound(int team);
    void ownSideInbound(int team);
    void setUpFreeThrowOffence(int number);
    void setUpFreeThrowDefence();
    void setUpStartGame();


    static const int PG = 1, SG = 2, SF = 3, PF = 4, C = 5;
    static const int TIGHT = 1, SAG = 2;
private:

    void readTeam(string teamName);

    map<int, Player*> players;
    map<int, int> defenceMatchups;
    map<int, int> defenceSettings;
    int team;
    string teamName;
};

#endif // TEAM_H
