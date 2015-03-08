#ifndef MATCHDEFENCE_H
#define MATCHDEFENCE_H
#include "Player.h"
#include "Team.h"
#include "Ball.h"
class MatchDefence
{
public:
    MatchDefence(Team *teamOne, Team *teamTwo);
protected:
    int* moveDefenceLoose(Player *p, Player *opposition);
    int* moveDefenceTight(Player* p, Player *opposition);
    int* moveTowardBasket(Player* p);
    int getOtherTeam(int team);

    Team *teams[2];
};

#endif // MATCHDEFENCE_H
