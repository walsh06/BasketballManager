#include "League.h"


/** League constructor */
League::League()
{
    initLeague();
}

/** League Destructor */
League::~League()
{
    for(auto &element: teams)
    {
        delete element.second;
    }
}

void League::initLeague()
{
    createSchedule("../BasketballManager/gameData/schedule.xml");
    teams[1] = new LeagueTeam("Spurs", true);
    teams[2] = new LeagueTeam("Pacers");
    teams[3] = new LeagueTeam("Heat");
    teams[4] = new LeagueTeam("Bobcats");
    currentRound = 1;
    teamCount = teams.size();
    results.clear();
}

/** Simulate a round of matches */
void League::simRound()
{
    //Get the matches for the current round
    vector<tuple<int, int>> matches = schedule[currentRound];

    for(auto &match: matches)
    {
        //get the home and away team
        LeagueTeam *homeTeam = teams[get<0>(match)];
        LeagueTeam *awayTeam = teams[get<1>(match)];

        //if one of the teams is usercontrolled temporarily set them to auto
        if(homeTeam->isUserControlled())
        {
            homeTeam->getTeam()->setUserControlled(false);
        }
        else if(awayTeam->isUserControlled())
        {
            awayTeam->getTeam()->setUserControlled(false);
        }

        //create the match and sim
        Match m(homeTeam->getTeam(), awayTeam->getTeam());
        m.setSimSpeed(0);
        m.sim();

        //get the final scores
        int scoreHome = m.getScore()[0], scoreAway = m.getScore()[1];

        //update the wins,losses,games
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

        //add a result
        results.push_back(homeTeam->getTeam()->getName() + " " + to_string(scoreHome) + "-" +
                                    to_string(scoreAway) +" "+awayTeam->getTeam()->getName());

        //set the team back to user controlled
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

/** Create the schedule by reading a file */
void League::createSchedule(const char* file)
{
    schedule.clear();
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(file);

    //loop through the tree structure created of the xml
    for (pugi::xml_node game: doc.child("schedule"))
    {
        map<string, int> gameMap;

        //get the number of teams and number of rounds
        roundCount = stoi(game.first_attribute().value());
        teamCount = stoi(game.last_attribute().value());

        //read the team numbers
        for (pugi::xml_attribute attr: game.attributes())
        {
            gameMap[attr.name()] = stoi(attr.value());
        }

        //create the matchup
        tuple <int, int> matchup = make_tuple(gameMap["home"], gameMap["away"]);
        int round = gameMap["round"];

        //add a new match to the round or create a new round
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

/** Get the winner/leader of the league */
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

/** Returns the round of matches */
vector<tuple<int, int>> League::getNextRound()
{
    return schedule[currentRound];
}
/** Returns the list of results*/
vector<string> League::getResults()
{
     return results;
}
/** Adds a new result */
void League::addResult(string newResult)
{
    results.push_back(newResult);
}
/** Returns the team for the given index */
LeagueTeam* League::getTeam(int index)
{
    return teams[index];
}
/** Get the match the user is playing in the current round */
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
/** Remove the users match from the current round */
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
/** Returns the list of all teams */
vector<LeagueTeam *> League::getAllTeams()
{
    vector<LeagueTeam *> allTeams;

    for(auto &team: teams)
    {
        allTeams.push_back(team.second);
    }

    return allTeams;
}
/** Returns the teams in order of wins */
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

/** Returns the number of teams in the league */
int League::getTeamCount()
{
    return teamCount;
}

//==================================
// Stats
//==================================

/** Returns the scoring leader for the given type */
string League::getScoringLeader(int type)
{
    //type 1 = point per game
    //type 2 = highest shooting percentage
    //type 3 = highest three point shooting percentage

    string teamName, playerName;
    float best = -1, current;

    for(auto &team: teams)
    {
        Team *currentTeam = team.second->getTeam();

        for(int i = 1; i <= currentTeam->getRosterSize(); i++)
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

/** Returns the rebound leader for the given type */
string League::getReboundLeader(int type)
{
    //type 1 = rebounds per game
    //type 2 = offensive rebounds per game
    //type 3 = defensive rebounds per game
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

/** Returns the leader of other categories */
string League::getOtherLeader(int type)
{
    //type 1 = assists per game
    //type 2 = blocks per game
    //type 3 = steals per game
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

/** Print the results */
void League::printResults()
{
    for(auto &result: results)
    {
        cout << result << endl;
    }
}

/** Print the league table */
void League::printTable()
{
    cout << "T|G|W|L" << endl;
    for(auto &team: teams)
    {
        cout << team.first << " " << team.second->getGames() << " " << team.second->getWins() << " " << team.second->getLosses() << endl;
    }
}

/** Print the schedule */
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

/** Print the schedule for a given team */
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

