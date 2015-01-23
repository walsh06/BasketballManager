#include "MatchScreen.h"
#include "ui_MatchScreen.h"

MatchScreen::MatchScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchScreen)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->court->setScene(scene);

    readXML();


    redBrush = new QBrush(Qt::red);
    blueBrush = new QBrush(Qt::blue);
    yellowBrush = new QBrush(Qt::yellow);
    blackPen = new QPen(Qt::black);

    positions = {"Point Guard", "Shooting Guard", "Small Forward", "Power Forward", "Centre"};
    strategies = {"Balanced", "Balanced Playmaker","Outside Playmaker", "Inside Playmaker",
                  "Inside Outside", "Rebounder", "Three Point", "Post Scorer"};

    swapIndexOne = 1;
    swapIndexTwo = 1;
}

MatchScreen::~MatchScreen()
{
    delete ui;
}
//======================================
// Tactics Screen
//======================================

void MatchScreen::initTacticScreen(Team *teamOne)
{
    this->teamOne = teamOne;
    for(auto position: positions)
    {
        ui->positionOne->addItem(position);
        ui->positionTwo->addItem(position);
        ui->positionThree->addItem(position);
        ui->positionFour->addItem(position);
        ui->positionFive->addItem(position);
    }
    ui->positionOne->setCurrentIndex(0);
    ui->positionTwo->setCurrentIndex(1);
    ui->positionThree->setCurrentIndex(2);
    ui->positionFour->setCurrentIndex(3);
    ui->positionFive->setCurrentIndex(4);

    for(auto strategy: strategies)
    {
        ui->strategyOne->addItem(strategy);
        ui->strategyTwo->addItem(strategy);
        ui->strategyThree->addItem(strategy);
        ui->strategyFour->addItem(strategy);
        ui->strategyFive->addItem(strategy);
        ui->quickStrategyOne->addItem(strategy);
        ui->quickStrategyTwo->addItem(strategy);
        ui->quickStrategyThree->addItem(strategy);
        ui->quickStrategyFour->addItem(strategy);
        ui->quickStrategyFive->addItem(strategy);
    }

    ui->ratingsWidget->setItem(0, 0, new QTableWidgetItem("3pt"));
    ui->ratingsWidget->setItem(0, 1, new QTableWidgetItem("Mid"));
    ui->ratingsWidget->setItem(0, 2, new QTableWidgetItem("Cls"));
    ui->ratingsWidget->setItem(0, 3, new QTableWidgetItem("Lay"));
    ui->ratingsWidget->setItem(0, 4, new QTableWidgetItem("Dnk"));
    ui->ratingsWidget->setItem(0, 5, new QTableWidgetItem("Pas"));
    ui->ratingsWidget->setItem(0, 6, new QTableWidgetItem("Def"));
    ui->ratingsWidget->setItem(0, 7, new QTableWidgetItem("Stl"));
    ui->ratingsWidget->setItem(0, 8, new QTableWidgetItem("Blk"));
    ui->ratingsWidget->setItem(0, 9, new QTableWidgetItem("ORb"));
    ui->ratingsWidget->setItem(0, 10, new QTableWidgetItem("DRb"));
    ui->ratingsWidget->setItem(0, 11, new QTableWidgetItem("Spd"));
    ui->ratingsWidget->setItem(0, 12, new QTableWidgetItem("FT"));
    initPlayers();
}

void MatchScreen::initPlayers()
{
    ui->playerWidget->clear();
    ui->swapPlayerOne->clear();
    ui->swapPlayerTwo->clear();
    for(int i = 1; i < 11; i++)
    {
        ui->playerWidget->addItem(QString::fromStdString(teamOne->getPlayer(i)->getName()));
        ui->swapPlayerOne->addItem(QString::fromStdString(teamOne->getPlayer(i)->getName()));
        ui->swapPlayerTwo->addItem(QString::fromStdString(teamOne->getPlayer(i)->getName()));
        QTableWidgetItem *three = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getThreeShot()));
        QTableWidgetItem *mid = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getMediumShot()));
        QTableWidgetItem *close = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getCloseShot()));
        QTableWidgetItem *layup = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getLayup()));
        QTableWidgetItem *dunk = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getDunk()));
        QTableWidgetItem *pass = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getPass()));
        QTableWidgetItem *defence = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getDefence()));
        QTableWidgetItem *steal = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getSteal()));
        QTableWidgetItem *block = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getBlock()));
        QTableWidgetItem *oRebound = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getOffRebound()));
        QTableWidgetItem *dRebound = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getDefRebound()));
        QTableWidgetItem *speed = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getSpeed()));
        QTableWidgetItem *freethrow = new QTableWidgetItem(QString::number(teamOne->getPlayer(i)->getFreethrow()));

        ui->ratingsWidget->setItem(i, 0, three);
        ui->ratingsWidget->setItem(i, 1, mid);
        ui->ratingsWidget->setItem(i, 2, close);
        ui->ratingsWidget->setItem(i, 3, layup);
        ui->ratingsWidget->setItem(i, 4, dunk);
        ui->ratingsWidget->setItem(i, 5, pass);
        ui->ratingsWidget->setItem(i, 6, defence);
        ui->ratingsWidget->setItem(i, 7, steal);
        ui->ratingsWidget->setItem(i, 8, block);
        ui->ratingsWidget->setItem(i, 9, oRebound);
        ui->ratingsWidget->setItem(i, 10, dRebound);
        ui->ratingsWidget->setItem(i, 11, speed);
        ui->ratingsWidget->setItem(i, 12, freethrow);
    }
}


//=================================
// Match Updates
//====================================

void MatchScreen::updateTime(int time, int shotClock)
{
    ui->clockShot->display(shotClock);

    ui->clockMinutes->display(time/60);
    ui->clockSeconds->display(time%60);
}

void MatchScreen::updateScore(int scoreOne, int scoreTwo)
{
    ui->scoreOne->display(scoreOne);
    ui->scoreTwo->display(scoreTwo);
}

void MatchScreen::updateCourt(std::vector<Player *> players, Ball *ball)
{
    scene->clear();
    QPixmap courtImage("../court.png");
    scene->addPixmap(courtImage.scaled(700,400, Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    int x, y, drawX, drawY, posModX, posModY, ballPos;

    for(int i =0; i < 14; i++)
    {
        int x = i * 50;
        scene->addLine(x, 0, x, 400, *blackPen);
    }
    for(int i =0; i < 8; i++)
    {
        int x = i * 50;
        scene->addLine(0, x, 700, x, *blackPen);
    }

    for(int i = 0; i < 10; i++)
    {
        if(ball->getTeam() == 2)
        {
            x = 6 - players[i]->getPosX();
        }
        else
        {
            x = players[i]->getPosX() + 7;
        }
        y = players[i]->getPosY();

        posModX = rand()%20;
        posModY = rand()%20;
        drawX = (x * 50) + posModX;
        drawY = (y * 50) + posModY;

        if(players[i]->getTeam() == 1)
        {
            scene->addEllipse(drawX, drawY, 30, 30, *blackPen, *redBrush);
        }
        else
        {
            scene->addEllipse(drawX, drawY, 30, 30, *blackPen, *blueBrush);
        }
    }

    if(ball->getTeam() == 2)
    {
        ballPos = (6 -  ball->getPosX()) * 50;
    }
    else
    {
        ballPos = (ball->getPosX() + 7) * 50;
    }
    scene->addEllipse(ballPos, ball->getPosY() * 50, 10, 10, *blackPen, *yellowBrush);
}

void MatchScreen::readXML()
{
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../commentary.xml");

    //loop through the tree structure created of the xml
    for (pugi::xml_node event: doc.child("commentary"))
    {

        int type = std::stoi(event.first_attribute().value());
        std::string commentary = event.last_attribute().value();

        if (comments.find(type) == comments.end())
        {
            std::vector<std::string> eventCommentary;
            eventCommentary.push_back(commentary);
            comments[type] = eventCommentary;
        }
        else
        {
            comments[type].push_back(commentary);
        }
    }
}

void MatchScreen::updateCommentary(int eventType, Player *p)
{
    int randPos = rand() % comments[eventType].size();
    string commentary = comments[eventType][randPos];

    commentary.replace(commentary.find("<player>"), 8, p->getName());

    ui->commentary->setText(QString::fromStdString(commentary));
}

//==========================
// Tactic Slots
//==========================
void MatchScreen::on_positionOne_currentIndexChanged(int index)
{
    emit changePosition(1, index+ 1);
}

void MatchScreen::on_positionTwo_currentIndexChanged(int index)
{
    emit changePosition(2, index+ 1);
}

void MatchScreen::on_positionThree_currentIndexChanged(int index)
{
    emit changePosition(3, index + 1);
}

void MatchScreen::on_positionFour_currentIndexChanged(int index)
{
    emit changePosition(4, index+ 1);
}

void MatchScreen::on_positionFive_currentIndexChanged(int index)
{
    emit changePosition(5, index+ 1);
}

void MatchScreen::on_tacticsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MatchScreen::on_matchButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MatchScreen::on_matchSpeed_sliderMoved(int position)
{
    emit changeSimSpeed(position);
}


void MatchScreen::on_StartPauseButton_clicked()
{
    emit startGame();
}

void MatchScreen::on_strategyOne_currentIndexChanged(int index)
{
    emit changeStrategy(1, index);
    ui->quickStrategyOne->setCurrentIndex(index);
}

void MatchScreen::on_strategyTwo_currentIndexChanged(int index)
{
    emit changeStrategy(2, index);
    ui->quickStrategyTwo->setCurrentIndex(index);

}

void MatchScreen::on_strategyThree_currentIndexChanged(int index)
{
    emit changeStrategy(3, index);
    ui->quickStrategyThree->setCurrentIndex(index);

}

void MatchScreen::on_strategyFour_currentIndexChanged(int index)
{
    emit changeStrategy(4, index);
    ui->quickStrategyFour->setCurrentIndex(index);

}

void MatchScreen::on_strategyFive_currentIndexChanged(int index)
{
    emit changeStrategy(5, index);
    ui->quickStrategyFive->setCurrentIndex(index);

}

void MatchScreen::on_playerWidget_currentRowChanged(int currentRow)
{

}

void MatchScreen::on_quickStrategyOne_currentIndexChanged(int index)
{
    emit changeStrategy(1, index);
    ui->strategyOne->setCurrentIndex(index);
}

void MatchScreen::on_quickStrategyTwo_currentIndexChanged(int index)
{
    emit changeStrategy(2, index);
    ui->strategyTwo->setCurrentIndex(index);
}

void MatchScreen::on_quickStrategyThree_currentIndexChanged(int index)
{
    emit changeStrategy(3, index);
    ui->strategyThree->setCurrentIndex(index);
}

void MatchScreen::on_quickStrategyFour_currentIndexChanged(int index)
{
    emit changeStrategy(4, index);
    ui->strategyFour->setCurrentIndex(index);

}

void MatchScreen::on_quickStrategyFive_currentIndexChanged(int index)
{
    emit changeStrategy(5, index);
    ui->strategyFive->setCurrentIndex(index);
}

void MatchScreen::on_swapButton_clicked()
{
    emit swapPlayers(swapIndexOne, swapIndexTwo);
    initPlayers();
}

void MatchScreen::on_swapPlayerOne_currentIndexChanged(int index)
{
    swapIndexOne = index + 1;
}

void MatchScreen::on_swapPlayerTwo_currentIndexChanged(int index)
{
    swapIndexTwo = index + 1;
}
