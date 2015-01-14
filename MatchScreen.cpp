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
    strategies = {"Outside Playmaker", "Inside Playmaker", "Inside Outside"};
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
    ui->playerOne->setText(QString::fromStdString(teamOne->getPlayer(1)->getName()));
    ui->playerTwo->setText(QString::fromStdString(teamOne->getPlayer(2)->getName()));
    ui->playerThree->setText(QString::fromStdString(teamOne->getPlayer(3)->getName()));
    ui->playerFour->setText(QString::fromStdString(teamOne->getPlayer(4)->getName()));
    ui->playerFive->setText(QString::fromStdString(teamOne->getPlayer(5)->getName()));

    for(auto position: positions)
    {
        ui->positionOne->addItem(position);
        ui->positionTwo->addItem(position);
        ui->positionThree->addItem(position);
        ui->positionFour->addItem(position);
        ui->positionFive->addItem(position);
    }

    for(auto strategy: strategies)
    {
        ui->strategyOne->addItem(strategy);
        ui->strategyTwo->addItem(strategy);
        ui->strategyThree->addItem(strategy);
        ui->strategyFour->addItem(strategy);
        ui->strategyFive->addItem(strategy);
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

void MatchScreen::on_swapButton_clicked()
{
    emit swapPlayers(checkOne, checkTwo);
}

void MatchScreen::on_playerOne_toggled(bool checked)
{
    if(checked == true)
    {
        if(checkCount < 2)
        {
            if(checkOne == -1)
            {

            }
        }
    }
    else
    {
        checkCount--;

    }
}


void MatchScreen::on_matchSpeed_sliderMoved(int position)
{
    emit changeSimSpeed(position);
}
