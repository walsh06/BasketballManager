#include "StatList.h"

/** StatList Default Constructor */
StatList::StatList()
{
    resetStats();
}

/** StatList Constructor taking a vector as parameter */
StatList::StatList(std::vector<int> stats)
{
    //init values to stats passed in
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

/** Reset all stats to 0 */
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

/** Write stats to a file */
void StatList::writeToFile(std::string filename, int pos)
{
    std::ofstream outfile;
    //open the file
      outfile.open(filename, std::ios_base::app);
      //write all stats to the file separated by commas
      outfile << "pos," << pos << ",points," << points << ",fga," << getShots() << ",3pa," << getThreeShots();
      outfile << ",trb," << getRebounds() << ",drb," << defensiveRebounds << ",orb," << offensiveRebounds;
      outfile << ",fta," << freeThrows << ",stl," << steals << ",blk," << blocks;
      outfile << ",ast," << getAssists() << ",mp," << minutes;
      if(getShots() == 0)
      {
          outfile << ",fgpc," << "nan";
      }
      else
      {
          outfile << ",fgpc," << getShootingPercentage();
      }
      if(threeShots == 0)
      {
           outfile <<  ",3ppc," << "nan";
      }
      else
      {
          outfile <<  ",3ppc," << getThreeShootingPercentage();
      }
      if(freeThrows == 0)
      {
          outfile <<  ",ftpc," << "nan" << "\n";
      }
      else
      {
          outfile <<  ",ftpc," << getFreeThrowPercentage() << "\n";
      }
      outfile.close();

}

/** Return game score of a player */
int StatList::getGameScore()
{
    //Calculated using John Hollingers game score formula
    return (points + (0.4 * scores) - (0.7 * shots) - (0.4 * (freeThrows - freeThrowsScored))
            + (0.7 * offensiveRebounds) + (0.3 * defensiveRebounds)
            + steals + (0.7 * assists) + (0.7 * blocks));

    /*
    Points Scored + (0.4 x Field Goals) – (0.7 x Field Goal Attempts)
    – (0.4 x (Free Throw Attempts – Free Throws)) + (0.7 x Offensive Rebounds)
    + (0.3 x Defensive Rebounds) + Steals + (0.7 x Assists) + (0.7 x Blocks)
    – (0.4 x Personal Fouls) – Turnovers*/
}

/** Overloaded plus operator */
StatList StatList::operator+(const StatList &list)
{
    //create a new vector
    std::vector<int> stats;

    //add two stats together
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

/** Increment games */
void StatList::addGame()
{
    games++;
}

/** Increment Minutes played */
void StatList::addMinute()
{
    minutes++;
}

/** Return total minutes */
int StatList::getMinutes()
{
    return minutes;
}

/** Return minutes per game */
float StatList::getMinutesPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)minutes/(float)games;
}

//==========================
// Points
//==========================
/** Increment points */
void StatList::addPoint()
{
    points++;
}

/** Add two points */
void StatList::addTwoPoints()
{
    points+=2;
    addScore();
}

/** Add three points */
void StatList::addThreePoints()
{
    points+=3;
    addThreeScore();
}

/** Increment shots */
void StatList::addMiss()
{
    shots++;
}

/** Increment scores */
void StatList::addScore()
{
    shots++;
    scores++;
}

/** Increment missed three attempts */
void StatList::addThreeMiss()
{
    threeShots++;
    addMiss();
}

/** Increment three point scores */
void StatList::addThreeScore()
{
    threeShots++;
    threeScores++;
    addScore();
}

/** Return total points */
int StatList::getPoints()
{
    return points;
}

/** Return points per game */
float StatList::getPointsPerGame()
{
    if(games == 0)
        return 0;
    else
        return float(points)/float(games);
}

/** Return total field goals */
int StatList::getFieldGoalsMade()
{
    return scores;
}

/** Return field goals per game */
float StatList::getFieldGoalsMadePerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)scores/(float)games;
}

/** Return total shots */
int StatList::getShots()
{
    return shots;
}

/** Return shots per game */
float StatList::getShotsPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)shots/(float)games;
}

/** Return total three attempts */
int StatList::getThreeShots()
{
    return threeShots;
}

/** Return three attempts get game */
float StatList::getThreeShotsPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)threeShots/(float)games;
}

/** Return shooting percentage */
float StatList::getShootingPercentage()
{
    if(shots == 0)
        return 0;
    else
        return float(scores)/float(shots);
}

/** Return three point shooting percentage */
float StatList::getThreeShootingPercentage()
{
    if(threeShots == 0)
        return 0;
    else
        return float(threeScores)/float(threeShots);
}

/** Print shooting stats to screen */
void StatList::printShootingStats()
{
    std::cout << "Points: " << points << " FGA: " << getShots() << " FG%: " << getShootingPercentage() << std::endl;
    std::cout << "3PA: " << getThreeShots() <<  " 3P% : " << getThreeShootingPercentage() << std::endl;
}

//===========================
// Rebounds
//===========================

/** Increment defensive rebounds */
void StatList::addDefensiveRebound()
{
    defensiveRebounds++;
}

/** Increment offensive rebounds */
void StatList::addOffensiveRebound()
{
    offensiveRebounds++;
}

/** Returns total rebounds */
int StatList::getRebounds()
{
    return defensiveRebounds + offensiveRebounds;
}

/** Returns rebounds per game */
float StatList::getReboundsPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)getRebounds()/(float)games;
}

/** Return total offensive rebounds */
int StatList::getOffensiveRebounds()
{
    return offensiveRebounds;
}

/** Return offensive rebounds per game */
float StatList::getOffensiveReboundsPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)offensiveRebounds/(float)games;
}

/** Return total defensive rebounds */
int StatList::getDefensiveRebounds()
{
    return defensiveRebounds;
}

/** Return defensive rebounds per game */
float StatList::getDefensiveReboundsPerGame()
{

    if(games == 0)
        return 0;
    else
        return (float)defensiveRebounds/(float)games;
}

/** Print rebound stats to console */
void StatList::printReboundingStats()
{
    std::cout << "Rebounds: " << getRebounds() << " OR: " << offensiveRebounds << " DR: " << defensiveRebounds << std::endl;
}

//===========================
// Assist
//===========================
/** Increment assists */
void StatList::addAssist()
{
    assists++;
}

/** Return total assists */
int StatList::getAssists()
{
    return assists;
}

/** Return assists per game */
float StatList::getAssistsPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)assists/(float)games;
}

/** Print assist stats to console */
void StatList::printAssistStats()
{
    std::cout << "Assists: " << getAssists() << std::endl;
}

//=============================
// Fouls and Free Throws
//=============================
/** Increment Free Throws */
void StatList::addFreeThrow()
{
    freeThrows++;
}

/** Increment Scored Free Throws */
void StatList::addFreeThrowScore()
{
    freeThrows++;
    freeThrowsScored++;
    points++;
}

/** Return free throw percentage */
float StatList::getFreeThrowPercentage()
{
    if(freeThrows == 0)
        return 0;
    else
        return float(freeThrowsScored)/float(freeThrows);
}

//==============================
// Defence Stats
//==============================
/** Increment Blocks */
void StatList::addBlock()
{
    blocks++;
}

/** Increment Steals */
void StatList::addSteal()
{
    steals++;
}

/** Return total blocks */
int StatList::getBlocks()
{
    return blocks;
}

/** Return blocks per game */
float StatList::getBlocksPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)blocks/(float)games;
}

/** Return total steals */
int StatList::getSteals()
{
    return steals;
}

/** Return steals per game */
float StatList::getStealsPerGame()
{
    if(games == 0)
        return 0;
    else
        return (float)steals/(float)games;
}
