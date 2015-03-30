#include "MatchDefenceMan.h"

MatchDefenceMan::MatchDefenceMan(Team *teamOne, Team *teamTwo):MatchDefence(teamOne, teamTwo)
{
}


std::vector<int> MatchDefenceMan::moveManDefence(Player *p, Ball *ball)
{
    ProbabilityVector probs(3);
    Team *team = teams[p->getTeam() - 1];
    int matchup, oppTeam = getOtherTeam(p->getTeam()), posValue, sag = 0, tight = 0, result;
    int defence = p->getDefence(), stealRating = p->getSteal(), defenceSetting;
    //get the defensive matchup of the player

    matchup = team->getMatchup(p);
    Player *opposition = teams[oppTeam]->getPlayer(matchup);
    if(ball->getPlayerPosition() == matchup)
    {
        posValue = opposition->getPosValue();
        defenceSetting = team->getDefenceSetting(matchup);

        if(defenceSetting == Team::TIGHT)
        {
            tight = 20 + posValue + defence;
            sag = (20 - defence)/2;
        }
        else
        {
            tight = (20 - defence)/2 + posValue;
            sag = 20 + defence;
        }

        probs.addProbability(tight);
        probs.addProbability(sag);

        if(opposition->getPosX() == p->getPosX() && opposition->getPosY() == p->getPosY())
        {
            probs.addProbability(stealRating);
        }

        result = probs.getRandomResult();
        if(result == 0)
        {
            return moveDefenceTight(p, opposition);
        }
        else if(result == 1)
        {
            return moveDefenceLoose(p, opposition);
        }
        else
        {
            return {-1,-1};
        }

    }
    else
    {
        posValue = opposition->getPosValue();
        defenceSetting = team->getDefenceSetting(matchup);

        if(defenceSetting == Team::TIGHT)
        {
            tight = 20 + posValue + defence;
            sag = (20 - defence)/2;
        }
        else
        {
            tight = (20 - defence)/2 + posValue;
            sag = 20 + defence;
        }

        probs.addProbability(tight);
        probs.addProbability(sag);

        vector<Player *> otherPlayers = teams[oppTeam]->getOtherPlayers(matchup);

        for(auto &player: otherPlayers)
        {
            if(player->isDribbleDrive())
            {
                probs.addProbability(10 + defence);
                break;
            }
        }

        result = probs.getRandomResult();
        if(result == 0)
        {
            return moveDefenceTight(p, opposition);
        }
        else if(result == 1)
        {
            return moveDefenceLoose(p, opposition);
        }
        else if(result == 2)
        {
            return moveTowardBasket(p);
        }
    }
}

std::vector<int> MatchDefenceMan::moveTowardBasket(Player* p)
{
    int posX = p->getPosX(), basketX = 6, basketY;

    if(posX < 4)
    {
        basketY = 3;
    }
    else
    {
        basketY = 4;
    }
    return {basketX, basketY};
}
