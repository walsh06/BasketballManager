#include "StatList.h"

StatList::StatList()
{
    points=0;
    games=1;

    shots = 0;
    scores = 0;
    threeScores = 0;
    threeShots = 0;


    offensiveRebounds=0;
    defensiveRebounds=0;

    assists = 0;
}

void StatList::addGame()
{
    games++;
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
