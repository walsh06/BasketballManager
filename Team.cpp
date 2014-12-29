#include "Team.h"

Team::Team()
{
    int pg = PG, sg = SG, sf = SF, pf = PF, c = C;
    players[pg] = new Player(1);
    players[sg] = new Player(2);
    players[sf] = new Player(3);
    players[pf] = new Player(4);
    players[c] = new Player(5);

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
