#include "MatchDefence.h"

MatchDefence::MatchDefence(Team *teamOne, Team *teamTwo)
{
    this->teams[0] = teamOne;
    this->teams[1] = teamTwo;
}
std::vector<int> MatchDefence::moveDefenceLoose(Player *p, Player *opposition)
{
    //get player and opposition positions
    int oppPosX = opposition->getPosX(), oppPosY = opposition->getPosY();

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

std::vector<int> MatchDefence::moveDefenceTight(Player* p, Player *opposition)
{
    int oppPosX = opposition->getPosX(), oppPosY = opposition->getPosY();
    return {oppPosX, oppPosY};
}

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

int MatchDefence::getOtherTeam(int team)
{
    if(team == 1) return 1;
    else return 0;
}
