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

    int getRebounds();
    void addOffensiveRebound();
    void addDefensiveRebound();
    void printReboundingStats();

    int getAssists();
    void addAssist();
    void printAssistStats();

private:
    int points, games;
    int assists;
    int threeScores, shots, threeShots, scores;
    int offensiveRebounds, defensiveRebounds;
};

#endif // STATLIST_H
