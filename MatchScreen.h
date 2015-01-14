#ifndef MATCHSCREEN_H
#define MATCHSCREEN_H

#include <QWidget>
#include "Player.h"
#include "Ball.h"
#include "Team.h"
#include "pugixml.hpp"

#include <vector>
#include <map>
#include <QGraphicsScene>

namespace Ui {
class MatchScreen;
}

class MatchScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MatchScreen(QWidget *parent = 0);
    ~MatchScreen();
    void updateCourt(std::vector<Player *> players, Ball *ball);
    void updateScore(int scoreOne, int scoreTwo);
    void updateTime(int time, int shotClock);
    void updateCommentary(int eventType, Player *p);

    void initTacticScreen(Team *teamOne);

private slots:
    void on_positionOne_currentIndexChanged(int index);

    void on_positionTwo_currentIndexChanged(int index);

    void on_tacticsButton_clicked();

    void on_matchButton_clicked();

    void on_positionThree_currentIndexChanged(int index);

    void on_positionFour_currentIndexChanged(int index);

    void on_positionFive_currentIndexChanged(int index);

    void on_swapButton_clicked();

    void on_playerOne_toggled(bool checked);

    void on_matchSpeed_sliderMoved(int position);

private:
    int checkOne, checkTwo, checkCount;
    Ui::MatchScreen *ui;
    QBrush * redBrush, *yellowBrush, *blueBrush;
    QPen * blackPen;
    vector<QString> positions, strategies;
    QGraphicsScene *scene;

     std::map<int, std::vector<std::string> > comments;

     void readXML();

signals:
    void swapPlayers(int, int);
    void changeStrategy(int, int);
    void changePosition(int, int);
    void changeSimSpeed(int);
};

#endif // MATCHSCREEN_H
