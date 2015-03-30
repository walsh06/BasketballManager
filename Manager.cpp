#include "Manager.h"

/** Manager Constructor */
Manager::Manager()
{
    energyThresholdSubIn = 90;
    energyThresholdSubOut = 80;
    subOutThreshold = 80;
}

/** Evaluate all players in a team */
void Manager::evaluatePlayers(map<int, Player *> players)
{
    playerRatings.clear();
    playerCount = players.size();

    //iterate through all players and calculate ratings
    for(int i = 1; i <= playerCount; i++)
    {
        Player *p = players[i];
        vector<float> player;
        //evaluate each strategy for the player
        //use the average of ratings for the strategy
        player.push_back(((float)p->getThreeShot() + (float)p->getMediumShot() + (float)p->getUnderBasketShot() + (float)p->getOffRebound())/4.0); //balanced
        player.push_back(((float)p->getThreeShot() + (float)p->getMediumShot() + (float)p->getSteal() + (float)p->getPass())/4.0); //outside playmaker
        player.push_back(((float)p->getLayup() + (float)p->getMediumShot() + (float)p->getCloseShot() + (float)p->getPass())/4.0); //inside playmaker
        player.push_back(((float)p->getThreeShot() + (float)p->getMediumShot() + (float)p->getLayup() + (float)p->getPass())/4.0); //balanced playmaker
        player.push_back(((float)p->getThreeShot() + (float)p->getMediumShot() + (float)p->getSteal())/3.0); //three point
        player.push_back(((float)p->getThreeShot() + (float)p->getCloseShot() + (float)p->getLayup() + (float)p->getDunk())/4.0); //inside outside
        player.push_back(((float)p->getLayup() + (float)p->getMediumShot() + (float)p->getCloseShot() + (float)p->getDunk())/4.0); //scoring forward
        player.push_back(((float)p->getCloseShot() + (float)p->getDunk() + (float)p->getLayup() + (float)p->getOffRebound())/4.0); //post scorer
        player.push_back(((float)p->getDunk() + (float)p->getBlock() + (float)p->getDefRebound() + (float)p->getOffRebound())/4.0); //rebound
        playerRatings.push_back(player);

        playerRatings[i-1].push_back(calculateMinutes(i));
    }
    //printRatings();
}

/** Pick a player to start in the given position */
void Manager::pickStartingPosition(int pos, map<int, Player *> &players)
{
    map<int, Player *> possibleSubs;
    float bestPos = playerRatings[pos - 1][getBestStrategyForPlayer(pos)];
    int bestPlayer = pos;
    //loop through all players and find eligible players
    for(int i=1; i <= players.size(); i++)
    {
        if(players[i]->getPlayingPosition() == pos)
        {
            possibleSubs[i] = players[i];
        }
    }

    if(possibleSubs.size() > 0)
    {
        //loop through possible subs
        for(auto &player: possibleSubs)
        {
            //find the player with the highest rating
            if(playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)] > bestPos)
            {
                bestPos = playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)];
                bestPlayer = player.first;
            }
        }
        //swap the player if a better player is found
        if(bestPlayer != pos)
        {
            Player *temp = players[pos];
            players[pos] = players[bestPlayer];
            players[bestPlayer] = temp;
            players[pos]->setPos(players[bestPlayer]->getPosX(), players[bestPlayer]->getPosY());
            swap(playerRatings[pos - 1], playerRatings[bestPlayer - 1]);
        }
    }
}

/** Advanced method to pick a starting player for a given position */
void Manager::pickStartingPositionAdvanced(int pos, map<int, Player *> &players)
{
    int start, end;
    map<int, Player *> possibleStarter;

    //loop through all players and find eligible players
    for(int i=pos; i <= players.size(); i++)
    {
        Player *player = players[i];
        //players are eligible if they are in the position or "next" to it
        if(player->getPlayingPosition() >= pos - 1 && player->getPlayingPosition() <= pos + 1)
        {
            possibleStarter[i] = player;
        }
    }
    if(possibleStarter.size() > 0)
    {
        //find the ratings range for the given position
        if(pos == 1)
        {
            start = 1; end = 3;
        }
        else if(pos == 2)
        {
            start = 1; end = 5;
        }
        else if(pos == 3)
        {
            start = 4; end = 6;
        }
        else if(pos == 4)
        {
            start = 5; end = 8;
        }
        else if(pos == 5)
        {
            start = 6; end = 8;
        }

        //get the index of the best player
        int bestPlayer = getBestPlayerForPosition(possibleStarter, start, end);
        //swap the player into the position
        if(bestPlayer != 0)
        {
            Player *temp = players[pos];
            players[pos] = players[bestPlayer];
            players[bestPlayer] = temp;
            players[pos]->setPos(players[bestPlayer]->getPosX(), players[bestPlayer]->getPosY());
            swap(playerRatings[pos - 1], playerRatings[bestPlayer - 1]);
        }
    }
}

/** Make a substitution in the given position */
void Manager::subPlayer(int pos, map<int, Player *> &players)
{
    //if the player is too tired they will be subbed
    if(players[pos]->getEnergy() < energyThresholdSubOut)
    {
        map<int, Player *> possibleSubs;
        float bestPos = 0.0;
        int bestPlayer = 0;
        //find eligible players for the position
        for(int i=6; i <= players.size(); i++)
        {
            //eligible if the position matches and they have enough energy
            if(players[i]->getPlayingPosition() == pos && players[i]->getEnergy() > energyThresholdSubIn)
            {
                possibleSubs[i] = players[i];
            }
        }

        //if there are eligible players to sub in
        if(possibleSubs.size() > 0)
        {
            //loop through eligible subs and pick the best one
            for(auto &player: possibleSubs)
            {
                if(playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)] > bestPos)
                {
                    bestPos = playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)];
                    bestPlayer = player.first;
                }
            }
            //swap the sub in
            if(bestPlayer != pos)
            {
                Player *temp = players[pos];
                players[pos] = players[bestPlayer];
                players[bestPlayer] = temp;
                players[pos]->setPos(players[bestPlayer]->getPosX(), players[bestPlayer]->getPosY());
                swap(playerRatings[pos - 1], playerRatings[bestPlayer - 1]);
                cout << "SUB " << pos << " " << bestPlayer << endl;
            }
        }
    }
}

/** Advanced method for subbing players */
void Manager::subPlayerAdvanced(int pos, map<int, Player *> &players, int time, int quarter)
{
    //calculate the time ratio
    float timeRatio = ((((quarter * 720)+(720.0- (float)time)) / 60.0) / 48.0);//calc portion of time elapsed

    //if the game is almost over, sub the starters back in
    if(timeRatio > 0.95)
    {
        pickStartingPosition(pos, players);
    }
    else
    {
        //calculate the subOutRating for the player in the game
        Player *subOut = players[pos];
        int subOutRating = subOut->getEnergy() + subOut->getStatList()->getGameScore()
                        + ((playerRatings[pos - 1][9] * timeRatio) - subOut->getStatList()->getMinutes());

        //check if the player is going to be subbed out if they are below the threshold
        if(subOutRating < subOutThreshold)
        {
            int start, end;
            map<int, Player *> possibleSubs;
            //find eligible subs on the bench
            for(int i=6; i <= players.size(); i++)
            {
                Player *player = players[i];
                //calculate the expected minutes of the sub at the current point of the game
                int minutes = player->getStatList()->getMinutes();
                int expectedTime = (playerRatings[i - 1][9] * timeRatio) * 1.25; //get expected current time of player + leeway
                //check if the player is eligible using energy, position and minutes
                if(players[i]->getEnergy() > energyThresholdSubIn && minutes < expectedTime
                   && player->getPlayingPosition() >= pos - 1 && player->getPlayingPosition() <= pos + 1)
                {
                    possibleSubs[i] = player;
                }
            }

            if(possibleSubs.size() > 0)
            {
                //find the ratings range for the given position
                if(pos == 1)
                {
                    start = 1; end = 3;
                }
                else if(pos == 2)
                {
                    start = 1; end = 5;
                }
                else if(pos == 3)
                {
                    start = 4; end = 6;
                }
                else if(pos == 4)
                {
                    start = 5; end = 8;
                }
                else if(pos == 5)
                {
                    start = 6; end = 8;
                }

                //find the best player for the position
                int bestPlayer = getBestPlayerForPosition(possibleSubs, start, end);
                //swap the sub into the team
                if(bestPlayer != 0)
                {
                    Player *temp = players[pos];
                    players[pos] = players[bestPlayer];
                    players[bestPlayer] = temp;
                    players[pos]->setPos(players[bestPlayer]->getPosX(), players[bestPlayer]->getPosY());
                    swap(playerRatings[pos - 1], playerRatings[bestPlayer - 1]);
                }
            }
        }
    }

}

/** Find the index of a players best strategy */
int Manager::getBestStrategyForPlayer(int playerPos)
{
    float best = playerRatings[playerPos - 1][0];
    int bestIndex = 0;
    for(int i = 0; i < 9; i++)
    {
        if(playerRatings[playerPos - 1][i] > best)
        {
            bestIndex = i;
            best = playerRatings[playerPos - 1][i];
        }
    }
    return bestIndex;
}

/** Find the player who is best at a given strategy */
int Manager::getBestPlayerForStrategy(int strategy)
{
    float best = playerRatings[0][strategy];
    int bestIndex = 0;
    for(int i = 1; i < playerCount; i++)
    {
        if(playerRatings[i][strategy] > best)
        {
            bestIndex = i;
            best = playerRatings[i][strategy];
        }
    }
    return bestIndex;
}

/** Find the player who is best at a certain position */
int Manager::getBestPlayerForPosition(map<int, Player *> players, int start, int end)
{
    int bestRating = 0, bestPlayer = 0;
    for(auto &player: players)
    {
        //get a players game score
        int playerScore = player.second->getStatList()->getGameScore() * 0.5;

        //check the player for the balanced strategy first
        if(playerRatings[player.first - 1][0] + playerScore > bestRating)
        {
            bestRating = playerRatings[player.first - 1][0] + playerScore;
            bestPlayer = player.first;
        }

        //check the player for the strategy range of a given position
        for(int i = start; i <= end; i++)
        {
            if(playerRatings[player.first - 1][i] + playerScore > bestRating)
            {
                bestRating = playerRatings[player.first - 1][i] + playerScore;
                bestPlayer = player.first;
            }
        }
    }
    return bestPlayer;
}

/** Calculate the minutes of a player */
float Manager::calculateMinutes(int index)
{
    float rating = playerRatings[index - 1][getBestStrategyForPlayer(index)];
    return rating * (rating / 10.0);
}

/** Print the evaluated ratings table */
void Manager::printRatings()
{
    for(int i = 0; i < playerCount; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            cout << playerRatings[i][j] << " ";
        }
        cout << endl;
    }
}
