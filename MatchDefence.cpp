#include "MatchDefence.h"

/** MatchDefence Constructor */
MatchDefence::MatchDefence(Team *teamOne, Team *teamTwo)
{
    this->teams[0] = teamOne;
    this->teams[1] = teamTwo;
}

/** Get the position a defender wants to move for loose defence */
int* MatchDefence::moveDefenceLoose(Player *p, Player *opposition)
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
    //return the result
    int result[2] = {oppPosX, oppPosY};
    return result;
}

/** Get the position a defender wants to move for tight defence */
int* MatchDefence::moveDefenceTight(Player* p, Player *opposition)
{
    int oppPosX = opposition->getPosX(), oppPosY = opposition->getPosY();
    int result[2] = {oppPosX, oppPosY};
    return result;
}

/** Function to return the other team value */
int MatchDefence::getOtherTeam(int team)
{
    if(team == 1) return 1;
    else return 0;
}
