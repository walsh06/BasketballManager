#include "Team.h"

Team::Team(string teamName)
{
    this->teamName = teamName;
    readTeam(teamName);

    setupTeamTactics();
}

void Team::readTeam(string teamName)
{
    int posCount = 1;
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../teams.xml");

        //loop through the tree structure created of the xml
        for (pugi::xml_node team: doc.child("teams"))
        {
            if(team.first_attribute().value() == teamName)
            {
                for(pugi::xml_node player: team.children())
                {
                    std::map<string, string> playerMap;

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

void Team::setupTeamTactics()
{
    manager.evaluatePlayers(players);
    for(int i = 1; i <= players.size(); i++)
    {
        int strategy = manager.getBestStrategyForPlayer(i);
        changeStrategy(i, strategy);
    }

    int pg = PG, sg = SG, sf = SF, pf = PF, c = C;

    defenceMatchups[pg] = PG;
    defenceMatchups[sg] = SG;
    defenceMatchups[sf] = SF;
    defenceMatchups[pf] = PF;
    defenceMatchups[c] = C;

    players[pg]->setPlayingPosition(new PositionPointGuard());
    players[sg]->setPlayingPosition(new PositionShootingGuard());
    players[sf]->setPlayingPosition(new PositionSmallForward());
    players[pf]->setPlayingPosition(new PositionPowerForward());
    players[c]->setPlayingPosition(new PositionCentre());
    players[6]->setPlayingPosition(new PositionPointGuard());
    players[7]->setPlayingPosition(new PositionShootingGuard());
    players[8]->setPlayingPosition(new PositionSmallForward());
    players[9]->setPlayingPosition(new PositionPowerForward());
    players[10]->setPlayingPosition(new PositionCentre());

    defenceSettings[pg] = TIGHT;
    defenceSettings[sg] = TIGHT;
    defenceSettings[sf] = TIGHT;
    defenceSettings[pf] = SAG;
    defenceSettings[c] = SAG;

    defence = MAN;
}

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

//===============================
int Team::getDefence()
{
    return defence;
}

void Team::setDefence(int defence)
{
    this->defence = defence;
}

vector<Player *> Team::getRoster()
{
    return roster;
}

Player* Team::getPlayer(int position)
{
    return players[position];
}

int Team::getPlayerPosition(int number)
{
    std::map<int, Player*>::const_iterator it;
    int pos;

    for(auto &player: players)
    {
        if(player.second->getNumber() == number)
        {
            pos = player.first;
            break;
        }
    }
    return pos;
}

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

int Team::getMatchup(int position)
{
    return defenceMatchups[position];
}

int Team::getMatchup(Player *p)
{
    return getMatchup(getPlayerPosition(p->getNumber()));
}

int Team::getDefenceSetting(int pos)
{
    return defenceSettings[pos];
}

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
        /*
       if(players[i]->getEnergy() < 80 && i < 6)
       {
           swapPlayers(i, i+5);
       }*/

   }
}

void Team::swapPlayers()
{
    for(int i = 1; i < 6; i++)
    {
        manager.subPlayer(i, players);
    }
}

void Team::swapPlayers(int ftShooter)
{
    for(int i = 1; i < 6; i++)
    {
        if(i != ftShooter)
        {
            manager.subPlayer(i, players);
        }
    }
}

//===========================================
// Team Set up
//===========================================
void Team::swapSides()
{
    for(auto &player: players)
    {
        Player *p = player.second;
        p->setPos((p->getPosX() *-1) - 1, p->getPosY());
    }
}

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

void Team::setUpFreeThrowDefence()
{
    getPlayer(1)->setPos(2, 2);
    getPlayer(2)->setPos(2, 5);
    getPlayer(3)->setPos(4, 2);
    getPlayer(4)->setPos(6, 5);
    getPlayer(5)->setPos(6, 2);
}

void Team::setUpStartGame()
{
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

int Team::getPressure(int posX, int posY)
{
   int count = 0;

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
   for(auto &player: players)
   {
       if(player.second->getPosX() == posX && player.second->getPosY() == posY)
       {
           count += 2;
       }
   }
   return count;
}

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

