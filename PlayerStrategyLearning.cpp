#include "PlayerStrategyLearning.h"

PlayerStrategyLearning::PlayerStrategyLearning(int threepa, int twopa, int ast, int orb, int games)
    :statLine({0, games, threepa + twopa, 0, threepa, 0, orb, 0, ast, 0, 0, 0, 0, 0})
{
    diffWeight = 0.5;
}

void PlayerStrategyLearning::writeToFile(Player *p)
{
    ProbabilityVector *currentVector = p->getStrategyVector();
    Heatmap *currentMap = p->getStrategy()->getMap();
    std::ofstream outfile;
    StatList *currentStats = p->getOverAllStatList();
    currentStats->writeToFile("../strategyLearning.csv", 1);

    outfile.open("../strategyLearning.csv", std::ios_base::app);
    outfile << p->getName() << endl;
    outfile << currentStats->getThreeShotsPerGame() << "," << currentStats->getShotsPerGame() - currentStats->getThreeShotsPerGame()<<",";
    outfile << currentStats->getAssistsPerGame() << "," << currentStats->getReboundsPerGame() << endl;

    for(int i = 0; i < 15; i++)
    {
        outfile << currentVector->getProbability(i) << ",";
    }
    outfile << endl;


    for(int i =0; i < 8; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            outfile << currentMap->getValue(j, i) << ",";
        }
        outfile << endl;
    }
    outfile.close();
}

void PlayerStrategyLearning::updateStrategy(Player *p)
{
    StatList *currentStats = p->getOverAllStatList();
    ProbabilityVector *currentVector = p->getStrategyVector();
    Heatmap *currentMap = p->getStrategy()->getMap();

    if(currentStats->getThreeShotsPerGame() < statLine.getThreeShotsPerGame() - diffWeight)
    {
        updateMapThree(currentMap, true);
    }
    else if(currentStats->getThreeShotsPerGame() > statLine.getThreeShotsPerGame() + diffWeight)
    {
        updateMapThree(currentMap, false);
    }

    if(currentStats->getShotsPerGame() - currentStats->getThreeShotsPerGame() <
      (statLine.getShotsPerGame() - statLine.getThreeShotsPerGame()) - diffWeight)
    {
        updateMapMid(currentMap, true);
        updateMapClose(currentMap, true);
    }
    else if(currentStats->getShotsPerGame() - currentStats->getThreeShotsPerGame() >
           (statLine.getShotsPerGame() - statLine.getThreeShotsPerGame()) + diffWeight)
    {
        updateMapMid(currentMap, false);
        updateMapClose(currentMap, false);
    }

    if(currentStats->getOffensiveReboundsPerGame() < statLine.getOffensiveReboundsPerGame() - diffWeight)
    {
        updateMapClose(currentMap, true);
    }
    else if(currentStats->getOffensiveReboundsPerGame() > statLine.getOffensiveReboundsPerGame() + diffWeight)
    {
        updateMapClose(currentMap, false);
    }

    if(currentStats->getAssistsPerGame() < statLine.getAssistsPerGame() - diffWeight)
    {
        currentVector->setProbability(10, currentVector->getProbability(10) + 1);
        currentVector->setProbability(11, currentVector->getProbability(11) + 1);
        currentVector->setProbability(12, currentVector->getProbability(12) + 1);
        currentVector->setProbability(13, currentVector->getProbability(13) + 1);
    }
    else if(currentStats->getAssistsPerGame() > statLine.getAssistsPerGame() + diffWeight)
    {
        currentVector->setProbability(10, currentVector->getProbability(10) - 1);
        currentVector->setProbability(11, currentVector->getProbability(11) - 1);
        currentVector->setProbability(12, currentVector->getProbability(12) - 1);
        currentVector->setProbability(13, currentVector->getProbability(13) - 1);
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
            map->incrementValue(i,0);
            map->incrementValue(i,7);
        }
        else
        {
            map->decrementValue(i,0);
            map->decrementValue(i,7);
        }
    }

    for(int i = 0; i < 8; i++)
    {
        if(increment)
        {
            map->incrementValue(0,i);
            map->incrementValue(1,i);
            if(i != 4 && i != 3)
            {
                map->incrementValue(2,i);
            }
        }
        else
        {
            map->decrementValue(0,i);
            map->decrementValue(1,i);
            if(i != 4 && i != 3)
            {
                map->decrementValue(2,i);
            }
        }
    }
}

void PlayerStrategyLearning::updateMapClose(Heatmap *map, bool increment)
{
    for(int i = 2; i < 6; i++)
    {
        for(int j = 4; j < 7; j++)
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

void PlayerStrategyLearning::updateMapMid(Heatmap *map, bool increment)
{
    for(int i = 3; i < 7; i++)
    {
        if(increment)
        {
            map->incrementValue(i, 1);
            map->incrementValue(i, 6);
            if(i == 3)
            {
                map->incrementValue(i, 2);
                map->incrementValue(i, 3);
                map->incrementValue(i, 4);
                map->incrementValue(i, 5);
            }
        }
        else
        {
            map->decrementValue(i, 1);
            map->decrementValue(i, 6);
            if(i == 3)
            {
                map->decrementValue(i, 2);
                map->decrementValue(i, 3);
                map->decrementValue(i, 4);
                map->decrementValue(i, 5);
            }
        }
    }
    if(increment)
    {
        map->incrementValue(2, 3);
        map->incrementValue(2, 4);
    }
    else
    {
        map->decrementValue(2, 3);
        map->decrementValue(2, 4);
    }
}
