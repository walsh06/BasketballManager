#ifndef ANALYSER_H
#define ANALYSER_H
#include <map>
#include <vector>
#include <fstream>

/*  This class is used for analysis of simulations. It can be dropped
 *  into the match class to take note of events such as shot times.
 *  It can the data to a csv file for later use.
 */
class Analyser
{
public:
    Analyser();

    void addDecision(int pos, int decision);
    void addShot(int time);

    void writeToFile();
private:
    std::map<int, std::vector<int>> decisionMap;

    std::map<int, int> shotMap;
};

#endif // ANALYSER_H
