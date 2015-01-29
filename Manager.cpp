#include "Manager.h"

Manager::Manager()
{

}

void Manager::evaluatePlayers(map<int, Player *> players)
{
    playerCount = players.size();

    for(int i = 1; i <= playerCount; i++)
    {
        Player *p = players[i];
        vector<float> player;
        player.push_back((p->getThreeShot() + p->getMediumShot() + p->getUnderBasketShot() + p->getOffRebound())/4); //balanced
        player.push_back((p->getThreeShot() + p->getMediumShot() + p->getSteal() + p->getPass())/4); //outside playmaker
        player.push_back((p->getDunk() + p->getBlock() + p->getDefRebound() + p->getOffRebound())/4); //rebound
        player.push_back((p->getCloseShot() + p->getDunk() + p->getLayup() + p->getOffRebound())/4); //post scorer
        player.push_back((p->getLayup() + p->getMediumShot() + p->getCloseShot() + p->getPass())/4); //inside playmaker
        player.push_back((p->getThreeShot() + p->getMediumShot() + p->getLayup() + p->getPass())/4); //balanced playmaker
        player.push_back((p->getThreeShot() + p->getCloseShot() + p->getLayup() + p->getDunk())/4); //inside outside
        player.push_back((p->getLayup() + p->getMediumShot() + p->getCloseShot() + p->getDunk())/4); //scoring forward
        player.push_back((p->getThreeShot() + p->getMediumShot() + p->getSteal())/3); //three point
        playerRatings.push_back(player);
    }
}

int Manager::getBestStrategyForPlayer(int playerPos)
{
    int best = playerRatings[playerPos][0], bestIndex = 0;
    for(int i = 1; i < 9; i++)
    {
        if(playerRatings[playerPos][i] > best)
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
