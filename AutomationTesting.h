#ifndef AUTOMATIONTESTING_H
#define AUTOMATIONTESTING_H

#include <vector>

#include "pugixml.hpp"
#include "Team.h"
#include "Match.h"

using namespace std;
class AutomationTesting
{
public:
    AutomationTesting();
    void runTests(int numSims);
private:
    vector<string> teamNames;
    void readTeams();

};

#endif // AUTOMATIONTESTING_H
