#include "AutomationTesting.h"

AutomationTesting::AutomationTesting()
{
    readTeams();
}

void AutomationTesting::runTests(int numSims)
{
    for(int i = 0; i < numSims; i++)
    {
        Team teamOne(teamNames[rand() % teamNames.size()]);
        Team teamTwo(teamNames[rand() % teamNames.size()]);

        Match m(&teamOne, &teamTwo);
        m.setSimSpeed(0);
        m.sim();
        string filename = string("../stats/Sim") + string(to_string(i)) + string(".csv");
        m.writeMatchStats(filename);
    }
}

void AutomationTesting::readTeams()
{
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../BasketballManager/gameData/teams.xml");

    //loop through the tree structure created of the xml
    for (pugi::xml_node team: doc.child("teams"))
    {
       teamNames.push_back(team.first_attribute().value());
    }
}
