#ifndef PLAYERSTRATEGYLEARNING_H
#define PLAYERSTRATEGYLEARNING_H
#include "StatList.h"
#include "Player.h"
#include "ProbabilityVector.h"
#include "Heatmap.h"

#include <iostream>
#include <fstream>

/* Class that handles strategy learning.
 * Manages the comparison of stats and
 * updating of the strategy in use */
class PlayerStrategyLearning
{
public:
    PlayerStrategyLearning(int threepa, int twopa, int ast, int orb, int games);

    void writeToFile(Player *p);
    void updateStrategy(Player *p);

private:
    StatList statLine;
    float diffWeight;

    void updateMapThree(Heatmap *map, bool increment);
    void updateMapMid(Heatmap *map, bool incremenet);
    void updateMapClose(Heatmap *map, bool increment);
};

#endif // PLAYERSTRATEGYLEARNING_H
