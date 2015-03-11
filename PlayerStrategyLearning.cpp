#include "PlayerStrategyLearning.h"

PlayerStrategyLearning::PlayerStrategyLearning():statLine({1452, 61, 1032, 501, 490, 207, 43, 226, 471, 269, 243, 2021,15, 132})
{
    diffWeight = 0.5;
}

void PlayerStrategyLearning::writeToFile(Player *p)
{

}

void PlayerStrategyLearning::updateStrategy(Player *p)
{
    StatList *currentStats = p->getStatList();
    ProbabilityVector *currentVector = p->getStrategyVector();
    Heatmap *currentMap = p->getStrategy()->getMap();

    if(currentStats->getThreeShotsPerGame() > statLine.getThreeShotsPerGame() - diffWeight)
    {

    }
    else if(currentStats->getThreeShotsPerGame() > statLine.getThreeShotsPerGame() + diffWeight)
    {

    }

    if(currentStats->getShotsPerGame() - currentStats->getThreeShotsPerGame() >
      (statLine.getShotsPerGame() - statLine.getThreeShotsPerGame()) - diffWeight)
    {

    }
    else if(currentStats->getShotsPerGame() - currentStats->getThreeShotsPerGame() >
           (statLine.getShotsPerGame() - statLine.getThreeShotsPerGame()) + diffWeight)
    {

    }


    if(currentStats->getReboundsPerGame() > statLine.getReboundsPerGame() - diffWeight)
    {

    }
    else if(currentStats->getReboundsPerGame() < statLine.getReboundsPerGame() + diffWeight)
    {

    }

    if(currentStats->getAssistsPerGame() < statLine.getAssistsPerGame() - diffWeight)
    {
        currentVector->setProbability(10, currentVector->getProbability(10) + 1);
    }
    else if(currentStats->getAssistsPerGame() > statLine.getAssistsPerGame() + diffWeight)
    {
        currentVector->setProbability(10, currentVector->getProbability(10) - 1);
    }

    if(currentStats->getShotsPerGame() < statLine.getShotsPerGame() - diffWeight)
    {
        currentVector->setProbability(9, currentVector->getProbability(9) + 1);
    }
    else if(currentStats->getShotsPerGame() > statLine.getShotsPerGame() + diffWeight)
    {
        currentVector->setProbability(9, currentVector->getProbability(9) - 1);
    }
}

void PlayerStrategyLearning::updateMapThree(Heatmap *map, bool increment)
{
    for(int i = 3; i < 7; i++)
    {
        if(increment)
        {
            map->incrementValue(0,i);
            map->incrementValue(7,i);
        }
        else
        {
            map->decrementValue(0,i);
            map->decrementValue(7,i);
        }
    }

    for(int i = 0; i < 8; i++)
    {
        if(increment)
        {
            map->incrementValue(i,0);
            map->incrementValue(i,1);
            if(i != 4 && i != 3)
            {
                map->incrementValue(i,2);
            }
        }
        else
        {
            map->decrementValue(i,0);
            map->decrementValue(i,1);
            if(i != 4 && i != 3)
            {
                map->decrementValue(i,2);
            }
        }
    }
}

void PlayerStrategyLearning::updateMapClose(Heatmap *map, bool increment)
{
    for(int i = 2; i < 6; i++)
    {
        for(int j = 4; i < 7; i++)
        {
            if(increment)
            {
                map->incrementValue(j, i);
            }
            else
            {
                map->decrementValue(j, i);
            }
        }
    }
}
