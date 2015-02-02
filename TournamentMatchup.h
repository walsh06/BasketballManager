#ifndef TOURNAMENTMATCHUP_H
#define TOURNAMENTMATCHUP_H
#include "Team.h"
class TournamentMatchup
{
public:
    TournamentMatchup(Team *teamOne, Team *teamTwo);
    void addWinOne();
    int getWinsOne();
    void addWinTwo();
    int getWinsTwo();

    Team* getTeamOne();
    Team* getTeamTwo();
private:
    Team *teamOne, *teamTwo;
    int winsOne, winsTwo;
};

#endif // TOURNAMENTMATCHUP_H
