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

}

Player* Team::getPlayer(int position)
{
    return players[position];
}

int Team::getPlayerPosition(int number)
{
    std::map<int, Player*>::const_iterator it;
    int pos;
    for (it = players.begin(); it != players.end(); ++it)
    {
        if (it->second->getNumber() == number)
        {
            pos = it->first;
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
