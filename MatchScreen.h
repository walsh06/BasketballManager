#ifndef MATCHSCREEN_H
#define MATCHSCREEN_H

#include <QWidget>
#include "Player.h"
#include "Ball.h"
#include "Team.h"
#include "pugixml.hpp"
#include "PlayerGraphic.h"
#include <vector>
#include <map>
#include <QGraphicsScene>
#include <QGridLayout>
#include <QComboBox>
#include <QGraphicsTextItem>

namespace Ui {
class MatchScreen;
}

class MatchScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MatchScreen(QWidget *parent = 0);
    ~MatchScreen();
    void updateCourt(Ball *ball);
    void updateScore(int scoreOne, int scoreTwo);
    void updateTime(int time, int shotClock);
    void updateCommentary(int eventType, Player *p, Player *p2 = NULL);

    void initTacticScreen(Team *teamOne);
    void initOppositionPlayers(Team *teamTwo);


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

    void on_swapButton_clicked();

    void on_swapPlayerOne_currentIndexChanged(int index);

    void on_swapPlayerTwo_currentIndexChanged(int index);

    void on_defenceType_currentIndexChanged(int index);

    void on_defenceType_2_currentIndexChanged(int index);

    void on_matchupOne_currentIndexChanged(int index);

    void on_matchupTwo_currentIndexChanged(int index);

    void on_matchupThree_currentIndexChanged(int index);

    void on_matchupFour_currentIndexChanged(int index);

    void on_matchupFive_currentIndexChanged(int index);

    void on_defenceButton_clicked();

    void on_defenceSettingOne_currentIndexChanged(int index);

    void on_defenceSettingTwo_currentIndexChanged(int index);

    void on_defenceSettingThree_currentIndexChanged(int index);

    void on_defenceSettingFour_currentIndexChanged(int index);

    void on_defenceSettingFive_currentIndexChanged(int index);

private:
    int swapIndexOne, swapIndexTwo;
    Ui::MatchScreen *ui;
    QBrush * redBrush, *yellowBrush, *blueBrush;
    QPen * blackPen;
    vector<QString> positions, strategies;
    QGraphicsScene *scene;
    vector<PlayerGraphic*> players;
    QGraphicsEllipseItem *ballCircle;
    Team *ownTeam, *oppositionTeam;
     std::map<int, std::vector<std::string> > comments;

     QComboBox *boxes[5][2], *defenceBoxes[5][2];

     void readXML();
     void initPlayers();
     void initCourt();

signals:
    void swapPlayers(int, int);
    void changeStrategy(int, int);
    void changePosition(int, int);
    void changeSimSpeed(int);
    void startGame();
    void changeDefenceType(int);
    void changeDefenceMatchup(int, int);
    void changeDefenceSetting(int, int);
};

#endif // MATCHSCREEN_H
