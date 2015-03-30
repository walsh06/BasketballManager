#ifndef MATCHDEFENCEZONE_H
#define MATCHDEFENCEZONE_H
#include "Player.h"
#include "Team.h"
#include "Ball.h"
#include "MatchDefence.h"

/* Defence class for zone defence
 */
class MatchDefenceZone:public MatchDefence
{
public:
    MatchDefenceZone(Team *teamOne, Team *teamTwo);
    int* moveZoneDefence(Player *p, Ball *ball);
private:
        int* moveTowardBasket(Player* p);
        int flipY(int y);
};

#endif // MATCHDEFENCEZONE_H
