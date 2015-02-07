#ifndef LEAGUE_H
#define LEAGUE_H
#include "Team.h"
#include "LeagueTeam.h"
#include "Match.h"
#include <map>
#include <tuple>
#include <vector>
using namespace std;
class League
{
public:
    League();

    void createSchedule(const char* file);
    int findWinner();

    void printSchedule();
    void printSchedule(int team);
    void printResults();
    void printTable();


    void simRound(int round);


private:
    map<int, LeagueTeam*> teams;

    map<int, vector<tuple<int, int>>> schedule;
    int roundCount, teamCount;
    vector<string> results;

};

#endif // LEAGUE_H
