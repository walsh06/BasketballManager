#include "MatchReceiver.h"

/** MatchReceiver Constructor */
MatchReceiver::MatchReceiver(Team *team, MatchScreen *screen, QObject *parent) :
    QObject(parent)
{
    this->team = team;
    //connect the signals from the GUI to slots in this class
    connect(screen, SIGNAL(swapPlayers(int, int)), this, SLOT(changePlayers(int, int)));
    connect(screen, SIGNAL(changePosition(int, int)), this, SLOT(changePosition(int, int)));
    connect(screen, SIGNAL(changeStrategy(int, int)), this, SLOT(changeStrategy(int, int)));
    connect(screen, SIGNAL(changeSimSpeed(int)), this, SLOT(changeSimSpeed(int)));
    connect(screen, SIGNAL(changeDefenceType(int)), this, SLOT(changeDefenceType(int)));
    connect(screen, SIGNAL(changeDefenceMatchup(int, int)), this, SLOT(changeDefenceMatchup(int, int)));
    connect(screen, SIGNAL(changeDefenceSetting(int, int)), this, SLOT(changeDefenceSetting(int, int)));

    simSpeed = 1000;
}

/** Queue a sub */
void MatchReceiver::changePlayers(int indexOne, int indexTwo)
{
    team->queueSubs(indexOne, indexTwo);
}

/** Change a players strategy */
void MatchReceiver::changeStrategy(int index, int strategy)
{
    team->changeStrategy(index, strategy);
}

/** Change a players position */
void MatchReceiver::changePosition(int index, int position)
{
    team->updatePosition(index, position);
}

/** Change the defence type of the team */
void MatchReceiver::changeDefenceType(int defenceType)
{
    team->setDefence(defenceType);
}

/** Change the simulation speed */
void MatchReceiver::changeSimSpeed(int index)
{
    switch(index)
    {
        case 0: simSpeed = 1000; break;
        case 1: simSpeed = 500; break;
        case 2: simSpeed = 250; break;
        case 3: simSpeed = 100; break;
        case 4: simSpeed = 0; break;
    }

    Match::setSimSpeed(simSpeed);
}

/** Get the simulation speed */
int* MatchReceiver::getSpeed()
{
    return &simSpeed;
}

/** Change defence matchups */
void MatchReceiver::changeDefenceMatchup(int opp, int pos)
{
    team->changeDefenceMatchup(opp, pos);
}

/** Change the defence setting of a player */
void MatchReceiver::changeDefenceSetting(int opp, int defence)
{
    team->setDefenceSetting(opp, defence);
}
