#include "LeagueTeam.h"

/** LeagueTeam Constructor */
LeagueTeam::LeagueTeam(string teamName, bool userControlled): team(teamName, userControlled)
{
     games = 0;
     wins = 0;
     this->userControlled = userControlled;
}

/** Add a game played */
void LeagueTeam::addGame()
{
    games++;
}

/** Add a win and game played */
void LeagueTeam::addWin()
{
    wins++;
    games++;
}

/** Return games played */
int LeagueTeam::getGames()
{
    return games;
}

/** Return wins */
int LeagueTeam::getWins()
{
    return wins;
}

/** Return losses */
int LeagueTeam::getLosses()
{
    return games-wins;
}

/** Return address of the team */
Team* LeagueTeam::getTeam()
{
    return &team;
}

/** Returns whether the team is user controlled */
bool LeagueTeam::isUserControlled()
{
    return userControlled;
}

/** Overloaded > operator to compare wins */
bool LeagueTeam::operator>(LeagueTeam &teamTwo)
{
    return wins > teamTwo.getWins();
}
