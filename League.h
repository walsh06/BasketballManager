#ifndef LEAGUE_H
#define LEAGUE_H
#include "Team.h"
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

    void printSchedule();
    void printSchedule(int team);

    void simRound(int round);


private:
    map<int, Team*> teams;

    map<int, vector<tuple<int, int>>> schedule;
    int roundCount, teamCount;

};

#endif // LEAGUE_H
