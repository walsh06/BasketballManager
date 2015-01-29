#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "Team.h"
#include "Match.h"

#include <map>
#include <vector>

using namespace std;

class Tournament
{
public:
    Tournament(int numTeams);
    void simRound();


private:
    map<int, Team*> teams;
    vector<tuple<int, int>> matches;
    int round;

    void createMatches(vector<int> teams);

};

#endif // TOURNAMENT_H
