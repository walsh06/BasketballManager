#include "Manager.h"

Manager::Manager()
{
    energyThresholdSubIn = 90;
    energyThresholdSubOut = 80;
    subOutThreshold = 80;
}

void Manager::evaluatePlayers(map<int, Player *> players)
{
    playerRatings.clear();
    playerCount = players.size();

    for(int i = 1; i <= playerCount; i++)
    {
        Player *p = players[i];
        vector<float> player;
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
    printRatings();
}

void Manager::pickStartingPosition(int pos, map<int, Player *> &players)
{
    map<int, Player *> possibleSubs;
    float bestPos = playerRatings[pos - 1][getBestStrategyForPlayer(pos)];
    int bestPlayer = pos;
    for(int i=1; i <= players.size(); i++)
    {
        if(players[i]->getPlayingPosition() == pos)
        {
            possibleSubs[i] = players[i];
        }
    }

    if(possibleSubs.size() > 0)
    {
        for(auto &player: possibleSubs)
        {
            if(playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)] > bestPos)
            {
                bestPos = playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)];
                bestPlayer = player.first;
            }
        }
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

void Manager::subPlayer(int pos, map<int, Player *> &players)
{
    if(players[pos]->getEnergy() < energyThresholdSubOut)
    {
        map<int, Player *> possibleSubs;
        float bestPos = 0.0;
        int bestPlayer = 0;
        for(int i=6; i <= players.size(); i++)
        {
            if(players[i]->getPlayingPosition() == pos && players[i]->getEnergy() > energyThresholdSubIn)
            {
                possibleSubs[i] = players[i];
            }
        }

        if(possibleSubs.size() > 0)
        {
            for(auto &player: possibleSubs)
            {
                if(playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)] > bestPos)
                {
                    bestPos = playerRatings[player.first - 1][getBestStrategyForPlayer(player.first)];
                    bestPlayer = player.first;
                }
            }
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

void Manager::subPlayerAdvanced(int pos, map<int, Player *> &players, int time, int quarter)
{
    float timeRatio = ((((quarter * 720)+(720.0- (float)time)) / 60.0) / 48.0);//calc portion of time elapsed

    if(timeRatio > 0.95)
    {
        pickStartingPosition(pos, players);
    }
    else
    {
        Player *subOut = players[pos];
        int subOutRating = subOut->getEnergy() + subOut->getStatList()->getGameScore()
                        + ((playerRatings[pos - 1][9] * timeRatio) - subOut->getStatList()->getMinutes());

        if(subOutRating < subOutThreshold)
        {
            int start, end;
            map<int, Player *> possibleSubs;
            for(int i=6; i <= players.size(); i++)
            {
                Player *player = players[i];
                int minutes = player->getStatList()->getMinutes();
                int expectedTime = (playerRatings[i - 1][9] * timeRatio) * 1.25; //get expected current time of player + leeway
                if(players[i]->getEnergy() > energyThresholdSubIn && minutes < expectedTime)
                {
                    possibleSubs[i] = player;
                }
            }
            if(possibleSubs.size() > 0)
            {
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

                int bestPlayer = getBestPlayerForPosition(possibleSubs, start, end);

                Player *temp = players[pos];
                players[pos] = players[bestPlayer];
                players[bestPlayer] = temp;
                players[pos]->setPos(players[bestPlayer]->getPosX(), players[bestPlayer]->getPosY());
                swap(playerRatings[pos - 1], playerRatings[bestPlayer - 1]);

            }
        }
    }

}

int Manager::getBestStrategyForPlayer(int playerPos)
{
    float best = playerRatings[playerPos - 1][0];
    int bestIndex = 0;
    for(int i = 1; i < 9; i++)
    {
        if(playerRatings[playerPos - 1][i] > best)
        {
            bestIndex = i;
            best = playerRatings[playerPos - 1][i];
        }
    }
    return bestIndex;
}

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

int Manager::getBestPlayerForPosition(map<int, Player *> players, int start, int end)
{
    int bestRating = 0, bestPlayer = 0;
    for(auto &player: players)
    {
        int playerScore = player.second->getStatList()->getGameScore() * 0.5;
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

float Manager::calculateMinutes(int index)
{
    float rating = playerRatings[index - 1][getBestStrategyForPlayer(index)];
    return rating * (rating / 10.0);
}

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
