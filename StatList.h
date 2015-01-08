#ifndef STATLIST_H
#define STATLIST_H

#include <iostream>

class StatList
{
public:
    StatList();
    void addGame();
    void addPoint();
    void addTwoPoints();
    void addThreePoints();
    void addThreeMiss();
    void addMiss();
    void addScore();
    void addThreeScore();
    float getPointsPerGame();
    int getShots();
    float getShootingPercentage();
    int getThreeShots();
    float getThreeShootingPercentage();
    void printShootingStats();

    void addRebound();

private:
    int points, rebounds, games, threeScores, shots, threeShots, scores;
};

#endif // STATLIST_H
