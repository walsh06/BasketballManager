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
    bool isMatchOver();
    void setMatchOver(bool over);
    Team* getTeamOne();
    Team* getTeamTwo();
private:
    Team *teamOne, *teamTwo;
    int winsOne, winsTwo;
    bool matchOver;
};

#endif // TOURNAMENTMATCHUP_H
