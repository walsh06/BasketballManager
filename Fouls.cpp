#include "Fouls.h"

Fouls::Fouls()
{
    resetFouls();
}

bool Fouls::getTeamBonus(int team)
{
    bool bonus = (team == 1) ? isTeamOneBonus() : isTeamTwoBonus();
    return bonus;
}

bool Fouls::isTeamOneBonus()
{
    return teamOneBonus;
}

bool Fouls::isTeamTwoBonus()
{
    return teamTwoBonus;
}

void Fouls::addFoul(int team, int time)
{
    if(team == 1)
    {
        teamOneFouls++;
        if(time < 120)
        {
            teamOneEndPeriodFouls++;
        }
        if(teamOneFouls >= 5 || teamOneEndPeriodFouls >= 2)
        {
            teamOneBonus = true;
        }
    }
    else
    {
        teamTwoFouls++;
        if(time < 120)
        {
            teamTwoEndPeriodFouls++;
        }

        if(teamTwoFouls >= 5 || teamTwoEndPeriodFouls >= 2)
        {
            teamTwoBonus = true;
        }
    }
}

void Fouls::resetFouls()
{
    teamOneBonus = false;
    teamTwoBonus = false;
    teamOneFouls = 0;
    teamTwoFouls = 0;
    teamOneEndPeriodFouls = 0;
    teamTwoEndPeriodFouls = 0;
}
