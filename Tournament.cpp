#include "Tournament.h"

Tournament::Tournament(int numTeams)
{
    round = 1;
    winsToProgress = 4;
    vector<int> startTeams;
    addTeam(new Team("Spurs"));
    addTeam(new Team("Heat"));
    addTeam(new Team("Pacers"));
    addTeam(new Team("Spurs"));
}

void Tournament::simRound()
{
    int numMatches = matches.size();
    for(int i = 0; i < numMatches; i++)
    {
        TournamentMatchup *match = matches[i];
        Team *teamOne = match->getTeamOne();
        Team *teamTwo = match->getTeamTwo();
        Match m(teamOne, teamTwo);
        int* score = m.getScore();

        if(score[0] > score[1])
        {
            match->addWinOne();
        }
        else
        {
            match->addWinTwo();
        }

        if(match->getWinsOne() == winsToProgress)
        {
            matches.erase(matches.begin() + i);
            winners.push_back(teamOne);
        }
        else if(match->getWinsTwo() == winsToProgress)
        {
            matches.erase(matches.begin() + i);
            winners.push_back(teamTwo);
        }
    }

    if(matches.size() == 0)
    {
        createMatches(winners);
        round++;
    }
}

void Tournament::addTeam(Team *team)
{
    winners.push_back(team);
}

void Tournament::createMatches(vector<Team *> teams)
{
    matches.clear();
    for(int i = 0; i < teams.size(); i+=2)
    {
        matches.push_back(new TournamentMatchup(teams[i], teams[i + 1]));
    }
}
