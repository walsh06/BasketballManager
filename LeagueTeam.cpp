#include "LeagueTeam.h"


LeagueTeam::LeagueTeam(string teamName, bool userControlled): team(teamName, userControlled)
{
     games = 0;
     wins = 0;
     this->userControlled = userControlled;
}

void LeagueTeam::addGame()
{
    games++;
}

void LeagueTeam::addWin()
{
    wins++;
    games++;
}

int LeagueTeam::getGames()
{
    return games;
}

int LeagueTeam::getWins()
{
    return wins;
}

int LeagueTeam::getLosses()
{
    return games-wins;
}

Team* LeagueTeam::getTeam()
{
    return &team;
}

bool LeagueTeam::isUserControlled()
{
    return userControlled;
}

bool LeagueTeam::operator>(LeagueTeam &teamTwo)
{
    return wins > teamTwo.getWins();
}
