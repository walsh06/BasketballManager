#include "PlayerStrategyLearning.h"

/** PLayerStrategyLearning Constructor */
PlayerStrategyLearning::PlayerStrategyLearning(int threepa, int twopa, int ast, int orb, int games)
    :statLine({0, games, threepa + twopa, 0, threepa, 0, orb, 0, ast, 0, 0, 0, 0, 0})
{
    //load the state line to be used for learning
    //init how much a stat can be away from the real player
    diffWeight = 0.5;
}

/** Write the strategy and stats to a file */
void PlayerStrategyLearning::writeToFile(Player *p)
{
    ProbabilityVector *currentVector = p->getStrategyVector();
    Heatmap *currentMap = p->getStrategy()->getMap();
    std::ofstream outfile;
    StatList *currentStats = p->getOverAllStatList();
    //write the stats to a file
    currentStats->writeToFile("../strategyLearning.csv", 1);

    //open the file
    outfile.open("../strategyLearning.csv", std::ios_base::app);
    outfile << p->getName() << endl;
    outfile << currentStats->getThreeShotsPerGame() << "," << currentStats->getShotsPerGame() - currentStats->getThreeShotsPerGame()<<",";
    outfile << currentStats->getAssistsPerGame() << "," << currentStats->getReboundsPerGame() << endl;

    //write the strategy influence values of the vector
    for(int i = 0; i < 15; i++)
    {
        outfile << currentVector->getProbability(i) << ",";
    }
    outfile << endl;

    //write the strategy influence values of the heatmap
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

/** Update the strategy of a player */
void PlayerStrategyLearning::updateStrategy(Player *p)
{
    //get the stats and the current strategy  influences
    StatList *currentStats = p->getOverAllStatList();
    ProbabilityVector *currentVector = p->getStrategyVector();
    Heatmap *currentMap = p->getStrategy()->getMap();

    //increase/decrease outside shots
    if(currentStats->getThreeShotsPerGame() < statLine.getThreeShotsPerGame() - diffWeight)
    {
        updateMapThree(currentMap, true);
    }
    else if(currentStats->getThreeShotsPerGame() > statLine.getThreeShotsPerGame() + diffWeight)
    {
        updateMapThree(currentMap, false);
    }

    //increase/decrease inside shots
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

    //increase/decrease rebounds
    if(currentStats->getOffensiveReboundsPerGame() < statLine.getOffensiveReboundsPerGame() - diffWeight)
    {
        updateMapClose(currentMap, true);
    }
    else if(currentStats->getOffensiveReboundsPerGame() > statLine.getOffensiveReboundsPerGame() + diffWeight)
    {
        updateMapClose(currentMap, false);
    }

    //increase/decrease assists/passing in the strategy vector
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

    // increase/decrease shots per game in the strategy vector
    if(currentStats->getShotsPerGame() < statLine.getShotsPerGame() - diffWeight)
    {
        currentVector->setProbability(9, currentVector->getProbability(9) + 1);
    }
    else if(currentStats->getShotsPerGame() > statLine.getShotsPerGame() + diffWeight)
    {
        currentVector->setProbability(9, currentVector->getProbability(9) - 1);
    }
}

/** Update the strategy map to for three point attempts */
void PlayerStrategyLearning::updateMapThree(Heatmap *map, bool increment)
{
    //loop through the positions of the heatmap representing three point shots
    //increment or decrement the value at each position
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

/** Update the strategy map close to the basket */
void PlayerStrategyLearning::updateMapClose(Heatmap *map, bool increment)
{
    //loop through the positions of the heatmap near the basket
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

/** Update the heatmap in the mid range of the court */
void PlayerStrategyLearning::updateMapMid(Heatmap *map, bool increment)
{
    //Loop through values in the mid range of the court and update
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
