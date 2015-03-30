#ifndef MATCHDEFENCE_H
#define MATCHDEFENCE_H
#include "Player.h"
#include "Team.h"
#include "Ball.h"

/* Class holding common defence functions.
 * Other defence classes sub class it.
 */
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
