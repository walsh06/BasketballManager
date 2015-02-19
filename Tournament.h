#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Team.h"
#include "Match.h"
#include "TournamentMatchup.h"

#include <map>
#include <vector>

using namespace std;

class Tournament
{
public:
    Tournament(int numTeams);
    void simRound();
    void addTeam(Team *team);


private:
    map<int, Team*> teams;
    vector<Team *> winners;
    vector<TournamentMatchup *> matches;
    int round, winsToProgress;

    void createMatches(vector<Team *> teams);

};

#endif // TOURNAMENT_H
