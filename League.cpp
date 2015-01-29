#include "League.h"

League::League()
{
    createSchedule("../schedule.xml");
}

void League::simRound(int round)
{
    vector<tuple<int, int>> matches = schedule[round];

    for(auto &match: matches)
    {
        Team *homeTeam = teams[get<0>(match)];
        Team *awayTeam = teams[get<1>(match)];
        Match m(homeTeam, awayTeam);
    }
}

void League::createSchedule(const char* file)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file);

    //loop through the tree structure created of the xml
    for (pugi::xml_node game: doc.child("schedule"))
    {
        map<string, int> gameMap;
        roundCount = stoi(game.first_attribute().value());
        teamCount = stoi(game.last_attribute().value());

        for (pugi::xml_attribute attr: game.attributes())
        {
            gameMap[attr.name()] = stoi(attr.value());
        }
        tuple <int, int> matchup = make_tuple(gameMap["home"], gameMap["away"]);
        int round = gameMap["round"];
        if(schedule.find(round) == schedule.end())
        {
            vector<tuple<int, int>> newRound;
            newRound.push_back(matchup);
            schedule[round] = newRound;
        }
        else
        {
            schedule[round].push_back(matchup);
        }
    }
}

void League::printSchedule()
{
    for(int i = 1; i <= roundCount; i++)
    {
        vector<tuple<int, int>> round = schedule[i];
        cout << "ROUND: " << i << endl;
        for(int j = 0; j < round.size(); j++)
        {
            cout << "HOME: " << get<0>(round[j]) << " AWAY: " << get<1>(round[j]) << endl;
        }
    }
}

void League::printSchedule(int team)
{
    for(int i = 1; i <= roundCount; i++)
    {
        vector<tuple<int, int>> round = schedule[i];
        cout << "ROUND: " << i << endl;
        for(int j = 0; j < round.size(); j++)
        {
            if(get<0>(round[j]) == team || get<1>(round[j]) == team)
            {
                cout << "HOME: " << get<0>(round[j]) << " AWAY: " << get<1>(round[j]) << endl;
            }
        }
    }
}

