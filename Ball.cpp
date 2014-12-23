#include "Ball.h"

Ball::Ball()
{
    team = 0;
    playerNumber = 0;
}

int Ball::getPlayerNumber()
{
    return playerNumber;
}
int Ball::getTeam()
{
    return team;
}

void Ball::setPlayerNumber(int num)
{
    playerNumber = num;
}

void Ball::setTeam(int team)
{
    if(team > 0 && team < 3)
    {
        this->team = team;
    }
}
