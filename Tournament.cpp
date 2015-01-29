#include "Tournament.h"

Tournament::Tournament(int numTeams)
{
    round = 1;
    vector<int> startTeams;
    for(int i = 1; i <= numTeams; i++)
    {
        teams[i] = new Team("spurs");
        startTeams.push_back(i);
    }
    createMatches(startTeams);
}

void Tournament::simRound()
{
    vector<int> winners;
    for(auto &match: matches)
    {
        Team *teamOne = teams[get<0>(match)];
        Team *teamTwo = teams[get<1>(match)];
        Match m(teamOne, teamTwo);
        int* score = m.getScore();
        if(score[0] > score[1])
        {
            winners.push_back(get<0>(match));
        }
        else
        {
            winners.push_back(get<1>(match));
        }
    }

    createMatches(winners);
    round++;
}

void Tournament::createMatches(vector<int> teams)
{
    matches.clear();
    for(int i = 0; i < teams.size(); i+=2)
    {
        matches.push_back(make_tuple(teams[i], teams[i+1]));
    }
}
