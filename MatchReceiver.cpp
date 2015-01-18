#include "MatchReceiver.h"

MatchReceiver::MatchReceiver(Team *team, MatchScreen *screen, QObject *parent) :
    QObject(parent)
{
    this->team = team;
    connect(screen, SIGNAL(swapPlayers(int, int)), this, SLOT(changePlayers(int, int)));
    connect(screen, SIGNAL(changePosition(int, int)), this, SLOT(changePosition(int, int)));
    connect(screen, SIGNAL(changeStrategy(int, int)), this, SLOT(changeStrategy(int, int)));
    connect(screen, SIGNAL(changeSimSpeed(int)), this, SLOT(changeSimSpeed(int)));
    simSpeed = 1000;
}

void MatchReceiver::changePlayers(int indexOne, int indexTwo)
{
    team->swapPlayers(indexOne, indexTwo);
}

void MatchReceiver::changeStrategy(int index, int strategy)
{
    team->updateStrategy(index, strategy);
}

void MatchReceiver::changePosition(int index, int position)
{
    team->updatePosition(index, position);
}

void MatchReceiver::changeSimSpeed(int index)
{
    switch(index)
    {
        case 0: simSpeed = 1000; break;
        case 1: simSpeed = 500; break;
        case 2: simSpeed = 250; break;
        case 3: simSpeed = 100; break;
    }

    Match::setSimSpeed(simSpeed);
}

int* MatchReceiver::getSpeed()
{
    return &simSpeed;
}
