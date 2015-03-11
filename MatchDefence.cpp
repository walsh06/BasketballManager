#include "MatchDefence.h"

MatchDefence::MatchDefence(Team *teamOne, Team *teamTwo)
{
    this->teams[0] = teamOne;
    this->teams[1] = teamTwo;
}
int* MatchDefence::moveDefenceLoose(Player *p, Player *opposition)
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
    int result[2] = {oppPosX, oppPosY};
    return result;
}

int* MatchDefence::moveDefenceTight(Player* p, Player *opposition)
{
    int oppPosX = opposition->getPosX(), oppPosY = opposition->getPosY();
    int result[2] = {oppPosX, oppPosY};
    return result;
}

int MatchDefence::getOtherTeam(int team)
{
    if(team == 1) return 1;
    else return 0;
}
