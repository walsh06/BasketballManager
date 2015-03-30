#ifndef MATCHDEFENCEZONE_H
#define MATCHDEFENCEZONE_H
#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "MatchDefence.h"
class MatchDefenceZone:public MatchDefence
{
public:
    MatchDefenceZone(Team *teamOne, Team *teamTwo);
    std::vector<int> moveZoneDefence(Player *p, Ball *ball);
private:
    int flipY(int y);
};

#endif // MATCHDEFENCEZONE_H
