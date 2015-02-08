#ifndef MATCHRECEIVER_H
#define MATCHRECEIVER_H

#include <QObject>
#include "Team.h"
#include "MatchScreen.h"
#include "Match.h"

class MatchReceiver : public QObject
{
    Q_OBJECT
public:
    explicit MatchReceiver(Team *team, MatchScreen *screen, QObject *parent = 0);
    int* getSpeed();
private:
    Team *team;
    int simSpeed;
signals:

public slots:
    void changePlayers(int indexOne, int indexTwo);
    void changeStrategy(int index, int strategy);
    void changePosition(int index, int position);
    void changeSimSpeed(int index);
    void changeDefenceType(int defenceType);
    void changeDefenceMatchup(int opp, int pos);
    void changeDefenceSetting(int opp, int defence);

};

#endif // MATCHRECEIVER_H
