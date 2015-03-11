#ifndef PLAYERSTRATEGYLEARNING_H
#define PLAYERSTRATEGYLEARNING_H
#include "StatList.h"
#include "Player.h"
#include "ProbabilityVector.h"
#include "Heatmap.h"
class PlayerStrategyLearning
{
public:
    PlayerStrategyLearning();

    void writeToFile(Player *p);
    void updateStrategy(Player *p);

private:
    StatList statLine;
    float diffWeight;

    void updateMapThree(Heatmap *map, bool increment);
    void updateMapClose(Heatmap *map, bool increment);
};

#endif // PLAYERSTRATEGYLEARNING_H
