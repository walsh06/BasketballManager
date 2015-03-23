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
    void runTests();
    void readTeams();
private:
    vector<string> teamNames;
};

#endif // AUTOMATIONTESTING_H
