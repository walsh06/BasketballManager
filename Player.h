#ifndef PLAYER_H
#define PLAYER_H

#include "StatList.h"
#include "Heatmap.h"
#include "PlayerPosition.h"
#include "PlayerStrategy.h"
#include "PositionCentre.h"
#include "PositionPointGuard.h"
#include "PositionPowerForward.h"
#include "PositionShootingGuard.h"
#include "PositionSmallForward.h"
#include <map>
using namespace std;

class Player
{
public:
    Player(int number);
    Player();
    Player(map<string, string> playerMap);

    ~Player();


    int getPosValue(int x, int y);
    int getPosValue();
    int getPosX();
    int getPosY();
    void setPos(int x, int y);
    void setRandomPos();
    void setPlayingPosition(PlayerPosition *pos);
    void setStrategy(PlayerStrategy *strategy);
    ProbabilityVector *getStrategyVector();
    PlayerStrategy *getStrategy();
    void updateMap();

    int getPlayingPosition();
    int getNumber();
    int getThreeShot();
    int getMediumShot();
    int getCloseShot();
    int getDunk();
    int getLayup();
    int getUnderBasketShot();
    int getOffRebound();
    int getDefRebound();
    int getFreethrow();
    int getBlock();
    int getSpeed();
    int getSteal();
    int getPass();
    int getDefence();

    int getStamina();
    int getEnergy();
    void resetEnergy();
    void updateEnergy(bool playing);
    int getEnergyModifier();

    void setTeam(int team);
    int getTeam();
    string getName();

    int getRange();

    void movePlayer(int direction);

    bool isDribbleDrive();
    void setDribbleDrive(bool drive);


    StatList* getStatList();
    StatList* getOverAllStatList();
    void updateOverAllStats();
    void resetGameStats();

    bool isLearning();
    void setLearning(bool learn);

    Heatmap moveTrackerMap;
private:

    Heatmap posValueMap, finalMap ;
    PlayerPosition *position;
    PlayerStrategy *strategy;
    StatList playerStatsGame, playerStatsOverAll;


    int posX, posY;
    int number, playingPosition;
    int team;
    string name;
    //shooting ratings
    int threeShot, mediumShot, closeShot, dunk, layup;
    //rebound
    int offRebound, defRebound;
    //defence
    int block, steal, defence;
    //offence
    int pass, hands, speed, freethrow;
    int energy, stamina;

    bool dribbleDrive;
    bool learning;
    void calcHeatMap();

    const int heatFactor = 3;
};

#endif // PLAYER_H
