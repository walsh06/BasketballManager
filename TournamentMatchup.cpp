#include "TournamentMatchup.h"

/** Tournament Constructor */
TournamentMatchup::TournamentMatchup(Team *teamOne, Team *teamTwo)
{
    matchOver = false;
    winsOne = 0;
    winsTwo = 0;
    this->teamOne = teamOne;
    this->teamTwo = teamTwo;
}

/** Increment team one wins */
void TournamentMatchup::addWinOne()
{
    winsOne++;
}

/** Return team one wins */
int TournamentMatchup::getWinsOne()
{
    return winsOne;
}

/** Increment team two wins */
void TournamentMatchup::addWinTwo()
{
    winsTwo++;
}

/** Return team two wins */
int TournamentMatchup::getWinsTwo()
{
    return winsTwo;
}

/** Return team one */
Team* TournamentMatchup::getTeamOne()
{
    return teamOne;
}

/** Return team two */
Team* TournamentMatchup::getTeamTwo()
{
    return teamTwo;
}

/** Return match over */
bool TournamentMatchup::isMatchOver()
{
    return matchOver;
}

/** Set the match over */
void TournamentMatchup::setMatchOver(bool over)
{
    matchOver = over;
}
