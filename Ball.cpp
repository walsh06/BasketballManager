#include "Ball.h"

Ball::Ball()
{
    team = 0;
    player = 0;
}

int Ball::getPlayerPosition()
{
    return player;
}
int Ball::getTeam()
{
    return team;
}

void Ball::setPlayerPosition(int num)
{
    player = num;
}

void Ball::setTeam(int team)
{
    if(team > 0 && team < 3)
    {
        this->team = team;
    }
}
