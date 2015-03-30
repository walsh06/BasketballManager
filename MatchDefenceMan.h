#ifndef MATCHDEFENCEMAN_H
#define MATCHDEFENCEMAN_H
#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "MatchDefence.h"
class MatchDefenceMan:public MatchDefence
{
public:
    MatchDefenceMan(Team *teamOne, Team *teamTwo);
    std::vector<int> moveManDefence(Player *p, Ball *ball);

private:
    std::vector<int> moveTowardBasket(Player* p);
};

#endif // MATCHDEFENCEMAN_H
