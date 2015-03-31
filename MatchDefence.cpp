#include "MatchDefence.h"

/** MatchDefence Constructor */
MatchDefence::MatchDefence(Team *teamOne, Team *teamTwo)
{
    this->teams[0] = teamOne;
    this->teams[1] = teamTwo;
}

/** Get the position a defender wants to move for loose defence */
std::vector<int> MatchDefence::moveDefenceLoose(Player *p, Player *opposition)
{
    //get player and opposition positions
    int oppPosX = opposition->getPosX(), oppPosY = opposition->getPosY();

    //adjust the position depending on the opposition
    if(oppPosX > 3)
    {
        if(oppPosY < 2)
        {
            oppPosY++;
        }
        else if(oppPosY > 5)
        {
            oppPosY--;
        }
    }
    else
    {
        if(oppPosY < 2)
        {
            oppPosY++;
        }
        else if(oppPosY > 5)
        {
            oppPosY--;
        }
        oppPosX++;
    }

    return {oppPosX, oppPosY};
}

/** Get the position a defender wants to move for tight defence */
std::vector<int> MatchDefence::moveDefenceTight(Player* p, Player *opposition)
{
    int oppPosX = opposition->getPosX(), oppPosY = opposition->getPosY();
    return {oppPosX, oppPosY};
}

/** Get the position to move towards the basket */
std::vector<int> MatchDefence::moveTowardBasket(Player* p)
{
    int posX = p->getPosX(), basketX = 6, basketY;

    if(posX < 4)
    {
        basketY = 3;
    }
    else
    {
        basketY = 4;
    }
    return {basketX, basketY};
}

/** Function to return the other team value */
int MatchDefence::getOtherTeam(int team)
{
    if(team == 1) return 1;
    else return 0;
}
