#include "Team.h"

/** Team Constructor */
Team::Team(string teamName, bool userControlled)
{
    this->userControlled = userControlled;
    this->teamName = teamName;
    readTeam(teamName);

    setupTeamTactics();
}

/** Team Destructor */
Team::~Team()
{
    for(auto &element: roster)
    {
        delete element;
    }
}

/** Read the team from xml file */
void Team::readTeam(string teamName)
{
    int posCount = 1;
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../BasketballManager/gameData/teams.xml");

        //loop through the tree structure created of the xml
        for (pugi::xml_node team: doc.child("teams"))
        {
            //find the specific team
            if(team.first_attribute().value() == teamName)
            {
                //loop through all players on the team
                for(pugi::xml_node player: team.children())
                {
                    std::map<string, string> playerMap;

                    //loop through all attributes of a player
                    for (pugi::xml_attribute attr: player.attributes())
                    {
                         playerMap[attr.name()] = attr.value();
                    }
                    players[posCount] = new Player(playerMap);
                    roster.push_back(players[posCount]);
                    posCount++;
                }
                break;
            }
        }
}

//==========================
// Tactics
//==========================
/** Manager sets up tactics of the team */
void Team::setupTeamTactics()
{
    //manager evaluates all players
    manager.evaluatePlayers(players);
    //loop through all players and assign their strategy
        for(int i = 1; i <= players.size(); i++)
        {
            if(!players[i]->isLearning())
            {
                int strategy = manager.getBestStrategyForPlayer(i);
                changeStrategy(i, strategy);
            }
        }

    //set the defence
    int pg = PG, sg = SG, sf = SF, pf = PF, c = C;

    defenceMatchups[pg] = PG;
    defenceMatchups[sg] = SG;
    defenceMatchups[sf] = SF;
    defenceMatchups[pf] = PF;
    defenceMatchups[c] = C;

    defenceSettings[pg] = TIGHT;
    defenceSettings[sg] = TIGHT;
    defenceSettings[sf] = TIGHT;
    defenceSettings[pf] = SAG;
    defenceSettings[c] = SAG;

    defence = MAN;
}

/** Manager picks starting team */
void Team::pickStartingTeam()
{
    for(int i = 1; i < 6; i++)
    {
        manager.pickStartingPosition(i, players);
    }
}

/** Change the strategy of a given player */
void Team::changeStrategy(int index, int strategy)
{
    PlayerStrategy *newStrategy;

    switch(strategy)
    {
        case 0: newStrategy = new PlayerStrategyBalanced(); break;
        case 1: newStrategy = new PlayerStrategyOutsidePlaymaker(); break;
        case 2: newStrategy = new PlayerStrategyInsidePlaymaker(); break;
        case 3: newStrategy = new PlayerStrategyBalancedPlaymaker(); break;
        case 4: newStrategy = new PlayerStrategyShootThree(); break;
        case 5: newStrategy = new PlayerStrategyInsideOutside(); break;
        case 6: newStrategy = new PlayerStrategyScoringForward(); break;
        case 7: newStrategy = new PlayerStrategyPostScorer(); break;
        case 8: newStrategy = new PlayerStrategyCrashBoards(); break;
    }

    players[index]->setStrategy(newStrategy);
}
//================================
// Defence
//================================
/** Return defence type */
int Team::getDefence()
{
    return defence;
}
/** Set defence type */
void Team::setDefence(int defence)
{
    this->defence = defence;
}
/** Change the matchup of a defender */
void Team::changeDefenceMatchup(int opp, int pos)
{
    int i;
    // find the defender currently guarding the player
    for(i = 1; i < 6; i++)
    {
        if(defenceMatchups[i] == opp)
        {
            break;
        }
    }
    //swap the matchups
    int temp = defenceMatchups[pos];
    defenceMatchups[pos] = opp;
    defenceMatchups[i] = temp;
}

/** Return defensive matchup for position */
int Team::getMatchup(int position)
{
    return defenceMatchups[position];
}

/** Return defensive matchup for player */
int Team::getMatchup(Player *p)
{
    return getMatchup(getPlayerPosition(p->getNumber()));
}

/** Return defence setting of a player */
int Team::getDefenceSetting(int pos)
{
    return defenceSettings[pos];
}

/** Set defence setting of a player */
int Team::setDefenceSetting(int pos, int defence)
{
    defenceSettings[pos] = defence;
}

//===============================
/** Return team name */
string Team::getName()
{
    return teamName;
}

/** Return roster size */
int Team::getRosterSize()
{
    return roster.size();
}

/** Return the roster of players */
vector<Player *> Team::getRoster()
{
    return roster;
}

/** Return player in position */
Player* Team::getPlayer(int position)
{
    return players[position];
}

/** Return player position for given number */
int Team::getPlayerPosition(int number)
{
    std::map<int, Player*>::const_iterator it;
    int pos;

    //loop through all players on the team
    for(auto &player: players)
    {
        //get the position of the player
        if(player.second->getNumber() == number)
        {
            pos = player.first;
            break;
        }
    }
    return pos;
}

/** Return other players on the court from given number */
vector<Player*> Team::getOtherPlayers(int number)
{
    vector<Player*> otherPlayers;
    for(int i = 1; i < 6; i++)
    {
        Player *p = players[i];
        if(p->getNumber() != number)
        {
            otherPlayers.push_back(p);
        }
    }

    return otherPlayers;
}

/** Set the team number */
void Team::setTeam(int team)
{
    if(team == 1 || team == 2)
    {
        this->team = team;
        for(auto &player: players)
        {
            player.second->setTeam(team);
        }
    }
}

//==========================================
// Tactics
//==========================================
/** Change the position of a given player */
void Team::updatePosition(int index, int position)
{
    PlayerPosition *newPosition;

    switch(position)
    {
        case PG: newPosition = new PositionPointGuard(); break;
        case SG: newPosition = new PositionShootingGuard(); break;
        case SF: newPosition = new PositionSmallForward(); break;
        case PF: newPosition = new PositionPowerForward(); break;
        case C: newPosition = new PositionCentre(); break;
    }

    players[index]->setPlayingPosition(newPosition);
}

/** Update the energy of all players */
void Team::updateEnergy()
{
   bool playing = true;
   for(int i = 1; i <= players.size(); i++)
   {
       if(i > 5)
       {
           playing = false;
       }
       players[i]->updateEnergy(playing);
   }
}

/** Put user subs into the queue */
void Team::queueSubs(int posOne, int posTwo)
{
    subsQueue.push_back(posOne);
    subsQueue.push_back(posTwo);
}

/** Make a substitution */
void Team::swapPlayers(int time, int quarter)
{
    if(userControlled)
    {
        //make subs from the queue
        for(int i = 0; i < subsQueue.size(); i+=2)
        {
            Player *tempPlayer = players[subsQueue[i]];
            players[subsQueue[i]] = players[subsQueue[i + 1]];
            players[subsQueue[i + 1]] = tempPlayer;
        }
    }
    else
    {
        //manager makes subs for AI team
        for(int i = 1; i < 6; i++)
        {
            manager.subPlayerAdvanced(i, players, time, quarter);
        }
    }
}

/** Make a substitution when a free throw occurs */
void Team::swapPlayers(int ftShooter, int time, int quarter)
{
    if(userControlled)
    {
        //make subs from the queue
        for(int i = 0; i < subsQueue.size(); i+=2)
        {
            Player *tempPlayer = players[subsQueue[i]];
            players[subsQueue[i]] = players[subsQueue[i + 1]];
            players[subsQueue[i + 1]] = tempPlayer;
        }
    }
    else
    {
        //manager makes subs for AI team, skipping the free throw shooter
        for(int i = 1; i < 6; i++)
        {
            if(i != ftShooter)
            {
                manager.subPlayerAdvanced(i, players, time, quarter);
            }
        }
    }
}

/** Return user control */
bool Team::isUserControlled()
{
    return userControlled;
}

/** Set user control */
void Team::setUserControlled(bool userControlled)
{
    this->userControlled = userControlled;
}

//===========================================
// Team Set up
//===========================================
/* These functions all take care of positioning players during
 * the game. Used for various game situations.
 */
/** Swap positions of all players */
void Team::swapSides()
{
    //multiply x by -1 to swap side
    for(auto &player: players)
    {
        Player *p = player.second;
        p->setPos((p->getPosX() *-1) - 1, p->getPosY());
    }
}

/** Set up the team when inbounding after a score */
void Team::restartInbound(int ballTeam)
{
    if(team == ballTeam)
    {
        getPlayer(1)->setPos(-5, 4);
        getPlayer(2)->setRandomPos();
        getPlayer(3)->setPos(-7, 4);
        getPlayer(4)->setRandomPos();
        getPlayer(5)->setRandomPos();

    }
    else
    {
        if(defence == ZONE)
        {
            getPlayer(1)->setPos(2, 3);
            getPlayer(2)->setPos(3, 5);
            getPlayer(3)->setPos(3, 2);
            getPlayer(4)->setPos(5, 5);
            getPlayer(5)->setPos(5, 2);
        }
        else
        {
            for(auto &player: players)
            {
                player.second->setRandomPos();
            }
        }

    }
}

/** Set up team if taking a free throw */
void Team::setUpFreeThrowOffence(int number)
{
    int pos = getPlayerPosition(number);

    getPlayer(pos)->setPos(3,4);

    if(pos < 4)
    {
        getPlayer(4)->setPos(5, 5);
        getPlayer(5)->setPos(5, 2);

        if(pos == 1)
        {
            getPlayer(2)->setPos(2, 6);
            getPlayer(3)->setPos(2, 1);
        }
        else if(pos == 2)
        {
            getPlayer(1)->setPos(2, 1);
            getPlayer(3)->setPos(2, 6);
        }
        else
        {
            getPlayer(1)->setPos(2, 1);
            getPlayer(2)->setPos(2, 6);
        }
    }
    else
    {
        getPlayer(1)->setPos(2, 1);
        getPlayer(2)->setPos(2, 6);
        if(pos == 4)
        {
            getPlayer(3)->setPos(5, 5);
            getPlayer(5)->setPos(5, 2);
        }
        else
        {
            getPlayer(3)->setPos(5, 2);
            getPlayer(4)->setPos(5, 5);
        }
    }
}

/** Set up team for opposition free throw */
void Team::setUpFreeThrowDefence()
{
    getPlayer(1)->setPos(2, 2);
    getPlayer(2)->setPos(2, 5);
    getPlayer(3)->setPos(4, 2);
    getPlayer(4)->setPos(6, 5);
    getPlayer(5)->setPos(6, 2);
}

/** Set up the start of the game at the start */
void Team::setUpStartGame()
{
    for(auto &player: players)
    {
        player.second->resetGameStats();
        player.second->resetEnergy();
    }

    if(team == 1)
    {
        getPlayer(1)->setPos(-3, 3);
        getPlayer(2)->setPos(-1, 1);
        getPlayer(3)->setPos(-1, 6);
        getPlayer(4)->setPos(-3, 4);
        getPlayer(5)->setPos(-1, 4);
    }
    else
    {
        getPlayer(1)->setPos(2, 3);
        getPlayer(2)->setPos(0, 1);
        getPlayer(3)->setPos(0, 6);
        getPlayer(4)->setPos(2, 4);
        getPlayer(5)->setPos(0, 3);
    }
}

/** Set up the team for their own inbound */
void Team::ownSideInbound(int team)
{
    if(this->team == team)
    {
        getPlayer(1)->setPos(-3, 2);
        getPlayer(2)->setRandomPos();
        getPlayer(3)->setRandomPos();
        getPlayer(4)->setPos(-3, 0);
        getPlayer(5)->setRandomPos();
    }
    else
    {
        for(auto &player: players)
        {
            player.second->setRandomPos();
        }
    }
}

/** Set up team for offensive inbound */
void Team::offensiveInbound(int team)
{
    if(this->team == team)
    {
        getPlayer(1)->setRandomPos();
        getPlayer(2)->setRandomPos();
        getPlayer(3)->setRandomPos();
        getPlayer(4)->setPos(3, 0);
        getPlayer(5)->setRandomPos();
    }
    else
    {
        for(auto &player: players)
        {
            player.second->setRandomPos();
        }
    }
}

//==============================================

/** Return pressure for the position x, y */
int Team::getPressure(int posX, int posY)
{
   int count = 0;

   //loop through positions in 3x3 grid and add to the pressure count
   for(int i = posY - 1; i <= posY + 1; i++)
   {
       for(int j = posX - 1; j <= posX + 1; j++)
       {
           for(auto &player: players)
           {
               if(player.second->getPosX() == j && player.second->getPosY() == i)
               {
                   count++;
               }
           }
       }
   }
   //add higher count if they are in the same position
   for(auto &player: players)
   {
       if(player.second->getPosX() == posX && player.second->getPosY() == posY)
       {
           count += 2;
       }
   }
   return count;
}

/** Return player count in given position */
vector<int> Team::getPlayersInPosition(int posX, int posY)
{
    vector<int> playersAtPos;
    for(int i = 1; i < 6; i++)
    {
        if(players[i]->getPosX() == posX && players[i]->getPosY() == posY)
        {
            playersAtPos.push_back(i);
        }
    }

    return playersAtPos;
}

/** Return player count under the basket */
int Team::getPlayersUnderBasket()
{
    int count = 0;
    for(auto &player: players)
    {
        if(player.second->getRange() == 1)
        {
            count++;
        }
    }
    return count;
}

