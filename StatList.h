#ifndef STATLIST_H
#define STATLIST_H

#include <vector>
#include <iostream>
#include <fstream>
class StatList
{
public:
    StatList();
    StatList(std::vector<int> stats);

    void resetStats();
    void addGame();
    void addMinute();
    int getMinutes();
    float getMinutesPerGame();
    void writeToFile(std::string filename, int pos);

    void addPoint();
    void addTwoPoints();
    void addThreePoints();
    void addThreeMiss();
    void addMiss();
    void addScore();
    void addThreeScore();
    int getPoints();
    float getPointsPerGame();
    int getShots();
    float getShotsPerGame();
    int getFieldGoalsMade();
    float getFieldGoalsMadePerGame();
    float getShootingPercentage();
    int getThreeShots();
    float getThreeShotsPerGame();
    float getThreeShootingPercentage();
    void printShootingStats();

    int getRebounds();
    float getReboundsPerGame();
    int getOffensiveRebounds();
    float getOffensiveReboundsPerGame();
    int getDefensiveRebounds();
    float getDefensiveReboundsPerGame();
    void addOffensiveRebound();
    void addDefensiveRebound();
    void printReboundingStats();

    int getAssists();
    float getAssistsPerGame();
    void addAssist();
    void printAssistStats();

    float getFreeThrowPercentage();
    void addFreeThrow();
    void addFreeThrowScore();

    void addBlock();
    void addSteal();
    int getBlocks();
    float getBlocksPerGame();
    int getSteals();
    float getStealsPerGame();

    StatList operator+(const StatList &list);

private:
    int points, games, minutes;
    int assists;
    int threeScores, shots, threeShots, scores;
    int offensiveRebounds, defensiveRebounds;
    int freeThrows, freeThrowsScored;
    int blocks, steals;
};

#endif // STATLIST_H
