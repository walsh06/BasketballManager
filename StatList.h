#ifndef STATLIST_H
#define STATLIST_H

#include <iostream>
#include <fstream>
class StatList
{
public:
    StatList();
    void addGame();
    void addMinute();
    int getMinutes();
    void writeToFile(std::string filename, int pos);

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

    float getFreeThrowPercentage();
    void addFreeThrow();
    void addFreeThrowScore();

    void addBlock();
    void addSteal();
    int getBlocks();
    int getSteals();

private:
    int points, games, minutes;
    int assists;
    int threeScores, shots, threeShots, scores;
    int offensiveRebounds, defensiveRebounds;
    int freeThrows, freeThrowsScored;
    int blocks, steals;
};

#endif // STATLIST_H
