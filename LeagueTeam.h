#ifndef LEAGUETEAM_H
#define LEAGUETEAM_H

#include "Team.h"

/* LeagueTeam is used to store a team in league mode
 * Tracks the wins, losses and games of the team
 */
using namespace std;
class LeagueTeam
{
public:
    LeagueTeam(string teamName, bool userControlled = false);

    void addGame();
    void addWin();
    int getGames();
    int getWins();
    int getLosses();
    bool isUserControlled();
    Team* getTeam();

    bool operator >(LeagueTeam &teamTwo);
private:
    Team team;
    int games, wins;
    bool userControlled;
};

#endif // LEAGUETEAM_H
