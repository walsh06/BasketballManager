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
#include <QGridLayout>

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

    void on_matchSpeed_sliderMoved(int position);

    void on_StartPauseButton_clicked();

    void on_strategyOne_currentIndexChanged(int index);

    void on_strategyTwo_currentIndexChanged(int index);

    void on_strategyThree_currentIndexChanged(int index);

    void on_strategyFour_currentIndexChanged(int index);

    void on_strategyFive_currentIndexChanged(int index);

    void on_playerWidget_currentRowChanged(int currentRow);

    void on_quickStrategyOne_currentIndexChanged(int index);

    void on_quickStrategyTwo_currentIndexChanged(int index);

    void on_quickStrategyFour_currentIndexChanged(int index);

    void on_quickStrategyFive_currentIndexChanged(int index);

    void on_quickStrategyThree_currentIndexChanged(int index);

private:
    int swapIndex;
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
    void startGame();
};

#endif // MATCHSCREEN_H
