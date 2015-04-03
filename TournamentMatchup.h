#ifndef TOURNAMENTMATCHUP_H
#define TOURNAMENTMATCHUP_H
#include "Team.h"

/* Class for managing a matchup during a tournament
 * Stores the teams and the wins of each team and the
 * progress of the round
 */
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
