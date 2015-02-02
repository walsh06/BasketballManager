#include "TournamentMatchup.h"

TournamentMatchup::TournamentMatchup(Team *teamOne, Team *teamTwo)
{
    matchOver = false;
    winsOne = 0;
    winsTwo = 0;
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

bool TournamentMatchup::isMatchOver()
{
    return matchOver;
}

void TournamentMatchup::setMatchOver(bool over)
{
    matchOver = over;
}
