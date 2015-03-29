#ifndef LEAGUE_H
#define LEAGUE_H
#include "Team.h"
#include "LeagueTeam.h"
#include "Match.h"
#include <map>
#include <tuple>
#include <vector>
#include <sstream>


/* The League class contains the functionality to run a league
 * Rounds can be simulated and the statistics are updated. Provides
 * methods to get leaderboard information, standings, fixtures and results
 */
using namespace std;
class League
{
public:
    League();
    ~League();

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
    void addResult(string newResult);
    LeagueTeam* getTeam(int index);
    void removeUserMatch();
    vector<LeagueTeam *> getAllTeams();
    int getTeamCount();

    vector<LeagueTeam *> getStandings();

    string getScoringLeader(int type);
    string getReboundLeader(int type);
    string getOtherLeader(int type);

private:
    map<int, LeagueTeam*> teams;

    map<int, vector<tuple<int, int>>> schedule;
    int roundCount, teamCount, currentRound;
    vector<string> results;
};

#endif // LEAGUE_H
