#include "Manager.h"

Manager::Manager()
{
    energyThresholdSubIn = 90;
    energyThresholdSubOut = 80;
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
    }
}

void Manager::pickStartingPosition(int pos, map<int, Player *> &players)
{
    map<int, Player *> possibleSubs;
    float bestPos = playerRatings[pos][getBestStrategyForPlayer(pos)];
    int bestPlayer = pos;
    for(int i=1; i <= players.size(); i++)
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
            for(int i = 0; i < 9; i++)
            {
                if(playerRatings[player.first - 1][i] > bestPos)
                {
                    bestPos = playerRatings[player.first - 1][i];
                    bestPlayer = player.first;
                }
            }
        }

        Player *temp = players[pos];
        players[pos] = players[bestPlayer];
        players[bestPlayer] = temp;
        players[pos]->setPos(players[bestPlayer]->getPosX(), players[bestPlayer]->getPosY());
        swap(playerRatings[pos], playerRatings[bestPlayer - 1]);
    }
}

void Manager::subPlayer(int pos, map<int, Player *> &players)
{
    if(players[pos]->getEnergy() < energyThresholdSubOut)
    {
        map<int, Player *> possibleSubs;
        float bestPos = 0.0;
        int bestPlayer = 0;
        for(int i=1; i <= players.size(); i++)
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
                for(int i = 0; i < 9; i++)
                {
                    if(playerRatings[player.first - 1][i] > bestPos)
                    {
                        bestPos = playerRatings[player.first - 1][i];
                        bestPlayer = player.first;
                    }
                }
            }

            Player *temp = players[pos];
            players[pos] = players[bestPlayer];
            players[bestPlayer] = temp;
            players[pos]->setPos(players[bestPlayer]->getPosX(), players[bestPlayer]->getPosY());
            swap(playerRatings[pos], playerRatings[bestPlayer - 1]);
            cout << "SUB " << pos << " " << bestPlayer << endl;
        }
    }
}

int Manager::getBestStrategyForPlayer(int playerPos)
{
    int best = playerRatings[playerPos - 1][0], bestIndex = 0;
    for(int i = 1; i < 9; i++)
    {
        if(playerRatings[playerPos - 1][i] > best)
        {
            bestIndex = i;
        }
    }
    return bestIndex;
}

int Manager::getBestPlayerForStrategy(int strategy)
{
    int best = playerRatings[0][strategy], bestIndex = 0;
    for(int i = 1; i < playerCount; i++)
    {
        if(playerRatings[i][strategy] > best)
        {
            bestIndex = i;
        }
    }
    return bestIndex;
}

void Manager::printRatings()
{
    for(int i = 0; i < playerCount; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << playerRatings[i][j] << " ";
        }
        cout << endl;
    }
}
