#include "Team.h"

Team::Team(string teamName)
{
    this->teamName = teamName;
    readTeam(teamName);

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

    players[c]->setStrategy(new PlayerStrategyCrashBoards());
    players[pf]->setStrategy(new PlayerStrategyCrashBoards());
    players[sf]->setStrategy(new PlayerStrategyInsideOutside());
    players[sg]->setStrategy(new PlayerStrategyShootThree());
    players[pg]->setStrategy(new PlayerStrategyOutsidePlaymaker());
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
                    posCount++;
                }
                break;
            }
        }
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
    for(auto &player: players)
    {
        if(player.second->getNumber() != number)
        {
            otherPlayers.push_back(player.second);
        }
    }

    return otherPlayers;
}

int Team::getMatchup(int position)
{
    return defenceMatchups[position];
}

int Team::getMatchup(Player p)
{
    return getMatchup(getPlayerPosition(p.getNumber()));
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
        for(auto &player: players)
        {
            player.second->setRandomPos();
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

