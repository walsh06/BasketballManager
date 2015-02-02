#include "TournamentMatchup.h"

TournamentMatchup::TournamentMatchup(Team *teamOne, Team *teamTwo)
{
    this->teamOne = teamOne;
    this->teamTwo = teamTwo;
}

void TournamentMatchup::addWinOne()
{
    winsOne++;
}

int TournamentMatchup::getWinsOne()
{
    return winsOne;
}

void TournamentMatchup::addWinTwo()
{
    winsTwo++;
}

int TournamentMatchup::getWinsTwo()
{
    return winsTwo;
}

Team* TournamentMatchup::getTeamOne()
{
    return teamOne;
}

Team* TournamentMatchup::getTeamTwo()
{
    return teamTwo;
}
