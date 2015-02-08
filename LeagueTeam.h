#ifndef LEAGUETEAM_H
#define LEAGUETEAM_H

#include "Team.h"

using namespace std;
class LeagueTeam
{
public:
    LeagueTeam(string teamName);

    void addGame();
    void addWin();
    int getGames();
    int getWins();
    int getLosses();

    Team* getTeam();
private:
    Team team;
    int games, wins;
};

#endif // LEAGUETEAM_H
