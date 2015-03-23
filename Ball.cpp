#include "Ball.h"

/** Ball constructor */
Ball::Ball()
{
    team = 1;
    player = 5;
}

/** Returns the position of the player in possession */
int Ball::getPlayerPosition()
{
    return player;
}
/** Returns team number of team in possession */
int Ball::getTeam()
{
    return team;
}

/** Set the player in possession */
void Ball::setPlayerPosition(int num)
{
    player = num;
}

/** Set the team in possession */
void Ball::setTeam(int team)
{
    if(team > 0 && team < 3)
    {
        this->team = team;
    }
}

/** Swap the team in possession */
void Ball::changeTeam()
{
    if(team == 1) team = 2;
    else if(team == 2) team = 1;
}

/** Change possession from the team passed in */
void Ball::changeTeam(int playerTeam)
{
    if(playerTeam == 1) team = 2;
    else if(playerTeam == 2) team = 1;
}
