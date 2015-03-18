#ifndef PLAYERSTRATEGYSCORINGFORWARD_H
#define PLAYERSTRATEGYSCORINGFORWARD_H
#include "PlayerStrategy.h"
class PlayerStrategyScoringForward : public PlayerStrategy
{
public:
    PlayerStrategyScoringForward();
    Heatmap* getMap();
    int getValue(int x, int y);
    ProbabilityVector* getWithBallVector();

private:
    Heatmap map;
    ProbabilityVector withBallVector;
};

#endif // PLAYERSTRATEGYSCORINGFORWARD_H
