#include "Team.h"

Team::Team()
{
    players[1] = new Player(1);
    players[2] = new Player(2);
    players[3] = new Player(3);
    players[4] = new Player(4);
    players[5] = new Player(5);
}

Player* Team::getPlayer(int number)
{
    return players[number];
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
