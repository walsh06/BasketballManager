#include "LeagueTeam.h"


LeagueTeam::LeagueTeam(string teamName): team(teamName)
{
     games = 0;
     wins = 0;
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
