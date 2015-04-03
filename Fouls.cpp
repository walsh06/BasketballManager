#include "Fouls.h"

/** Fouls Constructor */
Fouls::Fouls()
{
    resetFouls();
}

/** Returns the bonus for the given team */
bool Fouls::getTeamBonus(int team)
{
    return (team == 1) ? isTeamOneBonus() : isTeamTwoBonus();
}

/** Returns the team one bonus */
bool Fouls::isTeamOneBonus()
{
    return teamOneBonus;
}

/** Returns the team two bonus */
bool Fouls::isTeamTwoBonus()
{
    return teamTwoBonus;
}

/** Adds a foul for the given team*/
void Fouls::addFoul(int team, int time)
{
    //Check which team was fouled
    if(team == 1)
    {
        //update the foul count
        teamOneFouls++;

        //if in the final two minutes
        if(time < 120)
        {
            teamOneEndPeriodFouls++;
        }

        //set the bonus to true if the limits have been reached
        if(teamOneFouls >= 5 || teamOneEndPeriodFouls >= 2)
        {
            teamOneBonus = true;
        }
    }
    else
    {
        //update the foul count
        teamTwoFouls++;

        //if in the final two minutes
        if(time < 120)
        {
            teamTwoEndPeriodFouls++;
        }
        //set the bonus to true if the limits have been reached
        if(teamTwoFouls >= 5 || teamTwoEndPeriodFouls >= 2)
        {
            teamTwoBonus = true;
        }
    }
}

/** Resets fouls, used at the end of a quarter/game */
void Fouls::resetFouls()
{
    teamOneBonus = false;
    teamTwoBonus = false;
    teamOneFouls = 0;
    teamTwoFouls = 0;
    teamOneEndPeriodFouls = 0;
    teamTwoEndPeriodFouls = 0;
}
