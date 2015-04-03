#include "MatchDefenceMan.h"

/** MatchDefenceMan Constructor */
MatchDefenceMan::MatchDefenceMan(Team *teamOne, Team *teamTwo):MatchDefence(teamOne, teamTwo)
{
}

/** Get the position for a defender to move to in man defence*/
std::vector<int> MatchDefenceMan::moveManDefence(Player *p, Ball *ball)
{
    ProbabilityVector probs(3);
    Team *team = teams[p->getTeam() - 1];
    int matchup, oppTeam = getOtherTeam(p->getTeam()), posValue, sag = 0, tight = 0, result;
    int defence = p->getDefence(), stealRating = p->getSteal(), defenceSetting;
    //get the defensive matchup of the player
    matchup = team->getMatchup(p);
    Player *opposition = teams[oppTeam]->getPlayer(matchup);
    //if the defenders man has the ball
    if(ball->getPlayerPosition() == matchup)
    {
        posValue = opposition->getPosValue();
        defenceSetting = team->getDefenceSetting(matchup);

        //check the defensive setting for the player
        if(defenceSetting == Team::TIGHT)
        {
            //calculate the value for tight and sag choices
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

        //calculate the weight of an attempted steal
        if(opposition->getPosX() == p->getPosX() && opposition->getPosY() == p->getPosY())
        {
            probs.addProbability(stealRating);
        }

        //get a random result and return the values
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
        //else the matchup doesnt have the ball
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

        //calculate the weight of a player defending the basket
        for(auto &player: otherPlayers)
        {
            if(player->isDribbleDrive())
            {
                probs.addProbability(10 + defence);
                break;
            }
        }

        //get a random result and return the values
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

/** Get the position to move towards the basket */
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
