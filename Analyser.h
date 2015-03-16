#ifndef ANALYSER_H
#define ANALYSER_H
#include <map>
#include <vector>
#include <fstream>
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
