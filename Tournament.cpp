#include "Tournament.h"

/** Tournament Constructor */
Tournament::Tournament(int numTeams)
{
    round = 1;
    winsToProgress = 4;
    addTeam(new Team("Spurs"));
    addTeam(new Team("Heat"));
    addTeam(new Team("Pacers"));
    addTeam(new Team("Bobcats"));
    createMatches(winners);
    winners.clear();

}

/** Tournament Destructor */
Tournament::~Tournament()
{
    for(auto &element:teams)
    {
        delete element;
    }

    for(auto &element:matches)
    {
        delete element;
    }
}

/** Simulate a round of matches */
void Tournament::simRound()
{
    int numMatches = matches.size();
    //loop through all matches
    for(int i = 0; i < numMatches; i++)
    {
        TournamentMatchup *match = matches[i];
        //simulate match if the round isnt over
        if(match->isMatchOver() == false)
        {
            //get the two teams for the match and sim the match
            Team *teamOne = match->getTeamOne();
            Team *teamTwo = match->getTeamTwo();

            Match m(teamOne, teamTwo);
            m.setSimSpeed(0);
            m.sim();
            int* score = m.getScore();

            if(score[0] > score[1])
            {
                match->addWinOne();
            }
            else
            {
                match->addWinTwo();
            }

            //check if either team has enough wins to finish the round
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

    if(matches.size() == 1 && matches[0]->isMatchOver() == true)
    {
        cout << "TOURNAMENT OVER " << endl;
        cout << "WINNER " << winners[0]->getName() << endl;
    }
    else if(i == numMatches)
    {
        createMatches(winners);
        round++;
        winners.clear();
    }
}

/** Add a team to the tournament */
void Tournament::addTeam(Team *team)
{
    teams.push_back(team);
    winners.push_back(team);
}

/** Create the next round of matches */
void Tournament::createMatches(vector<Team *> teams)
{
    for(auto &match: matches)
    {
        matches.pop_back();
    }


    for(int i = 0; i < teams.size(); i+=2)
    {
        matches.push_back(new TournamentMatchup(teams[i], teams[i + 1]));
    }

}
