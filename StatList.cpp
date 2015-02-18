#include "StatList.h"

StatList::StatList()
{
    resetStats();
}

StatList::StatList(std::vector<int> stats)
{
    points=stats[0];
    games=stats[1];

    shots = stats[2];
    scores = stats[3];
    threeScores = stats[5];
    threeShots = stats[4];


    offensiveRebounds=stats[6];
    defensiveRebounds=stats[7];

    assists = stats[8];

    freeThrows = stats[9];
    freeThrowsScored = stats[10];

    minutes = stats[11];

    blocks = stats[12];
    steals = stats[13];
}

void StatList::resetStats()
{
    points=0;
    games=0;

    shots = 0;
    scores = 0;
    threeScores = 0;
    threeShots = 0;


    offensiveRebounds=0;
    defensiveRebounds=0;

    assists = 0;

    freeThrows = 0;
    freeThrowsScored = 0;

    minutes = 0;

    blocks = 0;
    steals = 0;
}

void StatList::writeToFile(std::string filename, int pos)
{
    std::ofstream outfile;

      outfile.open(filename, std::ios_base::app);
      outfile << "pos," << pos << ",points," << points << ",fga," << getShots() << ",fgpc," << getShootingPercentage() ;
      outfile << ",3pa," << getThreeShots() <<  ",3ppc," << getThreeShootingPercentage();
      outfile << ",trb," << getRebounds() << ",drb," << defensiveRebounds << ",orb," << offensiveRebounds;
      outfile << ",fta," << freeThrows << ",ftpc," << getFreeThrowPercentage();
      outfile << ",stl," << steals << ",blk," << blocks;
      outfile << ",ast," << getAssists() << ",mp," << minutes << "\n";
}

StatList StatList::operator+(const StatList &list)
{
    std::vector<int> stats;

    stats.push_back(points + list.points);
    stats.push_back(games + list.games);
    stats.push_back(shots + list.shots);
    stats.push_back(scores + list.scores);
    stats.push_back(threeShots + list.threeShots);
    stats.push_back(threeScores + list.threeScores);
    stats.push_back(offensiveRebounds + list.offensiveRebounds);
    stats.push_back(defensiveRebounds + list.defensiveRebounds);
    stats.push_back(assists + list.assists);
    stats.push_back(freeThrows + list.freeThrows);
    stats.push_back(freeThrowsScored + list.freeThrowsScored);
    stats.push_back(minutes + list.minutes);
    stats.push_back(blocks + list.blocks);
    stats.push_back(steals + list.steals);

    StatList newStatList(stats);

    return newStatList;
}

//==========================
// Time
//==========================

void StatList::addGame()
{
    games++;
}

void StatList::addMinute()
{
    minutes++;
}

int StatList::getMinutes()
{
    return minutes;
}

//==========================
// Points
//==========================
void StatList::addPoint()
{
    points++;
}

void StatList::addTwoPoints()
{
    points+=2;
    addScore();
}

void StatList::addThreePoints()
{
    points+=3;
    addThreeScore();
}

void StatList::addMiss()
{
    shots++;
}

void StatList::addScore()
{
    shots++;
    scores++;
}

void StatList::addThreeMiss()
{
    threeShots++;
    addMiss();
}

void StatList::addThreeScore()
{
    threeShots++;
    threeScores++;
    addScore();
}

float StatList::getPointsPerGame()
{
    return float(points)/float(games);
}

int StatList::getShots()
{
    return shots;
}

int StatList::getThreeShots()
{
    return threeShots;
}

float StatList::getShootingPercentage()
{
    return float(scores)/float(shots);
}

float StatList::getThreeShootingPercentage()
{
    return float(threeScores)/float(threeShots);
}

void StatList::printShootingStats()
{
    std::cout << "Points: " << points << " FGA: " << getShots() << " FG%: " << getShootingPercentage() << std::endl;
    std::cout << "3PA: " << getThreeShots() <<  " 3P% : " << getThreeShootingPercentage() << std::endl;
}

//===========================
// Rebounds
//===========================

void StatList::addDefensiveRebound()
{
    defensiveRebounds++;
}

void StatList::addOffensiveRebound()
{
    offensiveRebounds++;
}

int StatList::getRebounds()
{
    return defensiveRebounds + offensiveRebounds;
}

void StatList::printReboundingStats()
{
    std::cout << "Rebounds: " << getRebounds() << " OR: " << offensiveRebounds << " DR: " << defensiveRebounds << std::endl;
}

//===========================
// Assist
//===========================

void StatList::addAssist()
{
    assists++;
}

int StatList::getAssists()
{
    return assists;
}

void StatList::printAssistStats()
{
    std::cout << "Assists: " << getAssists() << std::endl;
}

//=============================
// Fouls and Free Throws
//=============================

void StatList::addFreeThrow()
{
    freeThrows++;
}

void StatList::addFreeThrowScore()
{
    freeThrows++;
    freeThrowsScored++;
}

float StatList::getFreeThrowPercentage()
{
    return float(freeThrowsScored)/float(freeThrows);
}

//==============================
// Defence Stats
//==============================

void StatList::addBlock()
{
    blocks++;
}

void StatList::addSteal()
{
    steals++;
}

int StatList::getBlocks()
{
    return blocks;
}

int StatList::getSteals()
{
    return steals;
}
