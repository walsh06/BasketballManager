#ifndef PLAYERSTRATEGYSCORINGFORWARD_H
#define PLAYERSTRATEGYSCORINGFORWARD_H
#include "PlayerStrategy.h"

/* Strategy for a forward who shoots more two point shots */
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
