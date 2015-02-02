#include "Tournament.h"

Tournament::Tournament(int numTeams)
{
    round = 1;
    winsToProgress = 4;
    addTeam(new Team("Spurs"));
    addTeam(new Team("Heat"));
    addTeam(new Team("Pacers"));
    addTeam(new Team("Spurs"));
    createMatches(winners);
}

void Tournament::simRound()
{
    int numMatches = matches.size();
    for(int i = 0; i < numMatches; i++)
    {

        TournamentMatchup *match = matches[i];
        if(match->isMatchOver() == false)
        {
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
                match->setMatchOver(true);
                winners.push_back(teamOne);
            }
            else if(match->getWinsTwo() == winsToProgress)
            {
                match->setMatchOver(true);
                winners.push_back(teamTwo);
            }
        }
    }
    int i;
    for(i = 0; i < numMatches && matches[i]->isMatchOver() == true; i++);

    if(i == numMatches)
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
