#ifndef MATCHDEFENCEMAN_H
#define MATCHDEFENCEMAN_H
#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "MatchDefence.h"

/* Defence class used for man to man defence
 */
class MatchDefenceMan:public MatchDefence
{
public:
    MatchDefenceMan(Team *teamOne, Team *teamTwo);
    int* moveManDefence(Player *p, Ball *ball);

private:
    int* moveTowardBasket(Player* p);
};

#endif // MATCHDEFENCEMAN_H
