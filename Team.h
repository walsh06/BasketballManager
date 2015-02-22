#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "PositionCentre.h"
#include "PositionPointGuard.h"
#include "PositionPowerForward.h"
#include "PositionShootingGuard.h"
#include "PositionSmallForward.h"
#include "PlayerStrategyBalanced.h"
#include "PlayerStrategyCrashBoards.h"
#include "PlayerStrategyShootThree.h"
#include "PlayerStrategyInsideOutside.h"
#include "PlayerStrategyOutsidePlaymaker.h"
#include "PlayerStrategyInsidePlaymaker.h"
#include "PlayerStrategyBalancedPlaymaker.h"
#include "PlayerStrategyPostScorer.h"
#include "PlayerStrategyBalanced.h"
#include "PlayerStrategyBalancedPlaymaker.h"
#include "PlayerStrategyScoringForward.h"
#include "Manager.h"

#include "pugixml.hpp"

#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Team
{
public:
    Team(string teamName, bool userControlled = false);
    vector<Player *> getRoster();
    string getName();
    Player* getPlayer(int position);
    vector<Player*> getOtherPlayers(int number);
    int getPlayerPosition(int number);
    int getMatchup(int position);
    int getMatchup(Player *p);
    int getPressure(int posX, int posY);
    int getPlayersUnderBasket();
    int getDefence();
    void setDefence(int defence);
    vector<int> getPlayersInPosition(int posX, int posY);
    int getDefenceSetting(int pos);
    void changeDefenceMatchup(int opp, int pos);
    int setDefenceSetting(int pos, int defence);
    void changeDefence(int defence);


    void queueSubs(int posOne, int posTwo);
    void swapPlayers(int time, int quarter);
    void swapPlayers(int ftShooter, int time, int quarter);

    void pickStartingTeam();
    void setupTeamTactics();
    void changeStrategy(int index, int strategy);
    void updateEnergy();
    void setTeam(int team);
    void updatePosition(int index, int strategy);
    void swapSides();

    void restartInbound(int team);
    void offensiveInbound(int team);
    void ownSideInbound(int team);
    void setUpFreeThrowOffence(int number);
    void setUpFreeThrowDefence();
    void setUpStartGame();

    bool isUserControlled();
    void setUserControlled(bool userControlled);

    static const int PG = 1, SG = 2, SF = 3, PF = 4, C = 5;
    static const int TIGHT = 1, SAG = 2;
    static const int ZONE = 1, MAN = 2;
private:

    void readTeam(string teamName);

    map<int, Player*> players;
    vector<Player *> roster;
    map<int, int> defenceMatchups;
    map<int, int> defenceSettings;
    vector<int> subsQueue;
    int team;
    string teamName;
    int defence;
    Manager manager;
    bool userControlled;
};

#endif // TEAM_H
