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

    bool isUserControlled();
    tuple<int, int> getUserMatch();
    void simRound();


    vector<tuple<int, int>> getNextRound();
    vector<string> getResults();
    LeagueTeam* getTeam(int index);
    void removeUserMatch();
    vector<LeagueTeam *> getAllTeams();
    int getTeamCount();

    vector<LeagueTeam *> getStandings();

    string getPointsLeader();
    string getFieldGoalLeader();
    string getThreePointLeader();


private:
    map<int, LeagueTeam*> teams;

    map<int, vector<tuple<int, int>>> schedule;
    int roundCount, teamCount, currentRound;
    vector<string> results;
};

#endif // LEAGUE_H
