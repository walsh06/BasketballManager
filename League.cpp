#include "League.h"

#include <sstream>
League::League()
{
    createSchedule("../schedule.xml");
    teams[1] = new LeagueTeam("Spurs");
    teams[2] = new LeagueTeam("Pacers");
    teams[3] = new LeagueTeam("Spurs");
    teams[4] = new LeagueTeam("Pacers");
}

void League::simRound(int round)
{
    vector<tuple<int, int>> matches = schedule[round];

    for(auto &match: matches)
    {
        /*
        Team *homeTeam = teams[get<0>(match)]->getTeam();
        Team *awayTeam = teams[get<1>(match)]->getTeam();
        Match m(homeTeam, awayTeam);
        m.sim();
        int scoreHome = m.getScore()[0], scoreAway = m.getScore()[1];
        if(scoreHome > scoreAway)
        {
            teams[get<0>(match)]->addWin();
            teams[get<1>(match)]->addGame();
        }
        else
        {
            teams[get<1>(match)]->addWin();
            teams[get<0>(match)]->addGame();
        }
        results.push_back(to_string(get<0>(match)) + " " + to_string(scoreHome) + "-" +
                                    to_string(scoreAway) +" "+to_string(get<1>(match)));
                                    */
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

int League::findWinner()
{
    int winner = 0;
    int wins = 0;
    for(auto &team: teams)
    {
        if(team.second->getWins() > wins)
        {
            winner = team.first;
            wins = team.second->getWins();
        }
    }
    return winner;
}

//==================================
// Printing
//==================================

void League::printResults()
{
    for(auto &result: results)
    {
        cout << result << endl;
    }
}

void League::printTable()
{
    cout << "T|G|W|L" << endl;
    for(auto &team: teams)
    {
        cout << team.first << " " << team.second->getGames() << " " << team.second->getWins() << " " << team.second->getLosses() << endl;
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

