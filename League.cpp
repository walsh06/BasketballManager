#include "League.h"

#include <sstream>
League::League()
{
    createSchedule("../BasketballManager/gameData/schedule.xml");
    teams[1] = new LeagueTeam("Spurs", true);
    teams[2] = new LeagueTeam("Pacers");
    teams[3] = new LeagueTeam("Heat");
    teams[4] = new LeagueTeam("Bobcats");
    currentRound = 1;
    teamCount = teams.size();
}

void League::simRound()
{
    vector<tuple<int, int>> matches = schedule[currentRound];

    for(auto &match: matches)
    {
        LeagueTeam *homeTeam = teams[get<0>(match)];
        LeagueTeam *awayTeam = teams[get<1>(match)];

        if(homeTeam->isUserControlled())
        {
            homeTeam->getTeam()->setUserControlled(false);
        }
        else if(awayTeam->isUserControlled())
        {
            awayTeam->getTeam()->setUserControlled(false);
        }
        Match m(homeTeam->getTeam(), awayTeam->getTeam());
        m.setSimSpeed(0);
        m.sim();
        int scoreHome = m.getScore()[0], scoreAway = m.getScore()[1];
        if(scoreHome > scoreAway)
        {
            homeTeam->addWin();
            awayTeam->addGame();
        }
        else
        {
            awayTeam->addWin();
            homeTeam->addGame();
        }
        results.push_back(homeTeam->getTeam()->getName() + " " + to_string(scoreHome) + "-" +
                                    to_string(scoreAway) +" "+awayTeam->getTeam()->getName());

        if(homeTeam->isUserControlled())
        {
            homeTeam->getTeam()->setUserControlled(true);
        }
        else if(awayTeam->isUserControlled())
        {
            awayTeam->getTeam()->setUserControlled(true);
        }
    }

    currentRound++;
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

//=================================
// GUI
//=================================

vector<tuple<int, int>> League::getNextRound()
{
    return schedule[currentRound];
}

vector<string> League::getResults()
{
     return results;
}

void League::addResult(string newResult)
{
    results.push_back(newResult);
}

LeagueTeam* League::getTeam(int index)
{
    return teams[index];
}

tuple<int, int> League::getUserMatch()
{
    vector<tuple<int, int>> matches = schedule[currentRound];

    for(auto &match: matches)
    {
        if(teams[get<0>(match)]->isUserControlled() || teams[get<1>(match)]->isUserControlled())
        {
            return match;
        }
    }
}

void League::removeUserMatch()
{
    vector<tuple<int, int>> matches = schedule[currentRound];

    for(int i = 0; i < matches.size(); i++)
    {
        tuple<int, int> match = matches[i];
        if(teams[get<0>(match)]->isUserControlled() || teams[get<1>(match)]->isUserControlled())
        {
            schedule[currentRound].erase(schedule[currentRound].begin() + i);
            break;
        }
    }
}

vector<LeagueTeam *> League::getAllTeams()
{
    vector<LeagueTeam *> allTeams;

    for(auto &team: teams)
    {
        allTeams.push_back(team.second);
    }

    return allTeams;
}

vector<LeagueTeam *> League::getStandings()
{
    vector<LeagueTeam *> allTeams = getAllTeams();
    vector<LeagueTeam *> standings;

    while(allTeams.size() > 0)
    {

        LeagueTeam *nextTeam = allTeams[allTeams.size() - 1];
        allTeams.pop_back();
        int i;
        for(i = standings.size(); i > 0; i--)
        {
            if(*standings[i - 1] > *nextTeam)
            {
                break;
            }
        }
        standings.insert(standings.begin() + i, nextTeam);
    }
    return standings;
}

int League::getTeamCount()
{
    return teamCount;
}

//==================================
// Stats
//==================================

string League::getScoringLeader(int type)
{
    string teamName, playerName;
    float best = -1, current;

    for(auto &team: teams)
    {
        Team *currentTeam = team.second->getTeam();

        for(int i = 1; i < currentTeam->getRosterSize(); i++)
        {
            if(type == 1)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getPointsPerGame();
            }
            else if(type == 2)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getShootingPercentage();
            }
            else if(type == 3)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getThreeShootingPercentage();
            }
            if(current > best)
            {
                best = current;
                teamName = currentTeam->getName();
                playerName = currentTeam->getPlayer(i)->getName();
            }
        }
    }

    string resultString = teamName + " : " + playerName + " : " + to_string(best);
    return resultString;
}

string League::getReboundLeader(int type)
{
    string teamName, playerName;
    float best = -1, current;

    for(auto &team: teams)
    {
        Team *currentTeam = team.second->getTeam();

        for(int i = 1; i <= currentTeam->getRosterSize(); i++)
        {
            if(type == 1)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getReboundsPerGame();
            }
            else if(type == 2)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getOffensiveReboundsPerGame();
            }
            else if(type == 3)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getDefensiveReboundsPerGame();
            }
            if(current > best)
            {
                best = current;
                teamName = currentTeam->getName();
                playerName = currentTeam->getPlayer(i)->getName();
            }
        }
    }

    string resultString = teamName + " : " + playerName + " : " + to_string(best);
    return resultString;
}

string League::getOtherLeader(int type)
{
    string teamName, playerName;
    float best = -1, current;

    for(auto &team: teams)
    {
        Team *currentTeam = team.second->getTeam();

        for(int i = 1; i <= currentTeam->getRosterSize(); i++)
        {
            if(type == 1)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getAssistsPerGame();
            }
            else if(type == 2)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getBlocksPerGame();
            }
            else if(type == 3)
            {
                current = currentTeam->getPlayer(i)->getOverAllStatList()->getStealsPerGame();
            }
            if(current > best)
            {
                best = current;
                teamName = currentTeam->getName();
                playerName = currentTeam->getPlayer(i)->getName();
            }
        }
    }

    string resultString = teamName + " : " + playerName + " : " + to_string(best);
    return resultString;
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

