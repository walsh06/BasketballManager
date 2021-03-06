#include "MatchScreen.h"
#include "ui_MatchScreen.h"

/** MatchScreen Constructor */
MatchScreen::MatchScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatchScreen)
{
    ui->setupUi(this);
    //set the court scene
    scene = new QGraphicsScene(this);
    ui->court->setScene(scene);

    //init brushes for colouring
    redBrush = new QBrush(Qt::red);
    blueBrush = new QBrush(Qt::blue);
    yellowBrush = new QBrush(Qt::yellow);
    blackPen = new QPen(Qt::black);

    positions = {"Point Guard", "Shooting Guard", "Small Forward", "Power Forward", "Centre"};
    strategies = {"Balanced", "Outside Playmaker", "Inside Playmaker", "Balanced Playmaker",
                  "Three Point","Inside Outside","Scoring Forward",  "Post Scorer", "Rebounder"};

    //load position combo boxes
    for(auto position: positions)
    {
        ui->positionOne->addItem(position);
        ui->positionTwo->addItem(position);
        ui->positionThree->addItem(position);
        ui->positionFour->addItem(position);
        ui->positionFive->addItem(position);
    }

    //load strategy combo boxes
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

    //load defence tactic boxes
    defenceBoxes[0][0] = ui->matchupOne;
    defenceBoxes[0][1] = ui->defenceSettingOne;
    defenceBoxes[1][0] = ui->matchupTwo;
    defenceBoxes[1][1] = ui->defenceSettingTwo;
    defenceBoxes[2][0] = ui->matchupThree;
    defenceBoxes[2][1] = ui->defenceSettingThree;
    defenceBoxes[3][0] = ui->matchupFour;
    defenceBoxes[3][1] = ui->defenceSettingFour;
    defenceBoxes[4][0] = ui->matchupFive;
    defenceBoxes[4][1] = ui->defenceSettingFive;

    for(int i = 0; i < 5; i++)
    {
        defenceBoxes[i][1]->addItem("Tight");
        defenceBoxes[i][1]->addItem("Sag");
        defenceBoxes[i][0]->addItem("PG");
        defenceBoxes[i][0]->addItem("SG");
        defenceBoxes[i][0]->addItem("SF");
        defenceBoxes[i][0]->addItem("PF");
        defenceBoxes[i][0]->addItem("C");

        defenceBoxes[i][0]->setCurrentIndex(i);
    }


    swapIndexOne = 1;
    swapIndexTwo = 1;
    initCourt();
}

/** MatchScreen Destructor */
MatchScreen::~MatchScreen()
{
    delete ui;
}
//======================================
// Tactics Screen
//======================================

/** Used to initialize aspects of the MatchScreen */
void MatchScreen::initMatchScreen(Team *teamOne, Team *teamTwo)
{
    //set the score
    ui->scoreOne->display(0);
    ui->scoreTwo->display(0);

    ui->teamOneName->setText(QString::fromStdString(teamOne->getName()));
    ui->teamTwoName->setText(QString::fromStdString(teamTwo->getName()));

    //set the user team
    if(teamTwo->isUserControlled())
    {
        this->ownTeam = teamTwo;
        this->oppositionTeam = teamOne;
    }
    else
    {
        this->ownTeam = teamOne;
        this->oppositionTeam = teamTwo;
    }

    initTacticScreen(ownTeam);
    initOppositionPlayers(oppositionTeam);
}

/** Initialize Player offensive tactics screen */
void MatchScreen::initTacticScreen(Team *team)
{
    //store tactic combo boxes
    boxes[0][0] = ui->positionOne; boxes[0][1] = ui->strategyOne;
    boxes[1][0] = ui->positionTwo; boxes[1][1] = ui->strategyTwo;
    boxes[2][0] = ui->positionThree; boxes[2][1] = ui->strategyThree;
    boxes[3][0] = ui->positionFour; boxes[3][1] = ui->strategyFour;
    boxes[4][0] = ui->positionFive; boxes[4][1] = ui->strategyFive;


    ui->positionOne->setCurrentIndex(0);
    ui->positionTwo->setCurrentIndex(1);
    ui->positionThree->setCurrentIndex(2);
    ui->positionFour->setCurrentIndex(3);
    ui->positionFive->setCurrentIndex(4);

    //load the ratings headings
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

/** Initialize the players on the users team */
void MatchScreen::initPlayers()
{
    //clear current values
    ui->playerWidget->clear();
    ui->quickPlayerList->clear();
    ui->swapPlayerOne->clear();
    ui->swapPlayerTwo->clear();

    //loop through all players and add them to the screen
    for(int i = 1; i <= ownTeam->getRosterSize(); i++)
    {
        //load the player name and number
        ui->playerWidget->addItem(QString::number(ownTeam->getPlayer(i)->getNumber()) + QString::fromStdString(" " +ownTeam->getPlayer(i)->getName()));
        //load the players on the court to the quick tab
        if(i < 6)
        {
            ui->quickPlayerList->addItem(QString::number(ownTeam->getPlayer(i)->getNumber()) + QString::fromStdString(" " + ownTeam->getPlayer(i)->getName()));
        }
        //load the subs combo boxes
        ui->swapPlayerOne->addItem(QString::fromStdString(ownTeam->getPlayer(i)->getName()));
        ui->swapPlayerTwo->addItem(QString::fromStdString(ownTeam->getPlayer(i)->getName()));

        //load the players ratings
        QTableWidgetItem *three = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getThreeShot()));
        QTableWidgetItem *mid = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getMediumShot()));
        QTableWidgetItem *close = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getCloseShot()));
        QTableWidgetItem *layup = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getLayup()));
        QTableWidgetItem *dunk = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getDunk()));
        QTableWidgetItem *pass = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getPass()));
        QTableWidgetItem *defence = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getDefence()));
        QTableWidgetItem *steal = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getSteal()));
        QTableWidgetItem *block = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getBlock()));
        QTableWidgetItem *oRebound = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getOffRebound()));
        QTableWidgetItem *dRebound = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getDefRebound()));
        QTableWidgetItem *speed = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getSpeed()));
        QTableWidgetItem *freethrow = new QTableWidgetItem(QString::number(ownTeam->getPlayer(i)->getFreethrow()));

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

    loadStats();
}

/** Initialize the opposition team on the GUI */
void MatchScreen::initOppositionPlayers(Team *team)
{
    //clear the names
    ui->oppPlayerNames->clear();
    //load ratings headings
    ui->oppPlayerRatings->setItem(0, 0, new QTableWidgetItem("3pt"));
    ui->oppPlayerRatings->setItem(0, 1, new QTableWidgetItem("Mid"));
    ui->oppPlayerRatings->setItem(0, 2, new QTableWidgetItem("Cls"));
    ui->oppPlayerRatings->setItem(0, 3, new QTableWidgetItem("Lay"));
    ui->oppPlayerRatings->setItem(0, 4, new QTableWidgetItem("Dnk"));
    ui->oppPlayerRatings->setItem(0, 5, new QTableWidgetItem("Pas"));
    ui->oppPlayerRatings->setItem(0, 6, new QTableWidgetItem("Def"));
    ui->oppPlayerRatings->setItem(0, 7, new QTableWidgetItem("Stl"));
    ui->oppPlayerRatings->setItem(0, 8, new QTableWidgetItem("Blk"));
    ui->oppPlayerRatings->setItem(0, 9, new QTableWidgetItem("ORb"));
    ui->oppPlayerRatings->setItem(0, 10, new QTableWidgetItem("DRb"));
    ui->oppPlayerRatings->setItem(0, 11, new QTableWidgetItem("Spd"));
    ui->oppPlayerRatings->setItem(0, 12, new QTableWidgetItem("FT"));

    //loop through the players on the court
    for(int i = 1; i < 6; i++)
    {
        Player *player = oppositionTeam->getPlayer(i);
        //load the player name and number
        ui->oppPlayerNames->addItem(QString::number(player->getNumber()) + QString::fromStdString(" " + player->getName()));
        //load the players ratings
        QTableWidgetItem *three = new QTableWidgetItem(QString::number(player->getThreeShot()));
        QTableWidgetItem *mid = new QTableWidgetItem(QString::number(player->getMediumShot()));
        QTableWidgetItem *close = new QTableWidgetItem(QString::number(player->getCloseShot()));
        QTableWidgetItem *layup = new QTableWidgetItem(QString::number(player->getLayup()));
        QTableWidgetItem *dunk = new QTableWidgetItem(QString::number(player->getDunk()));
        QTableWidgetItem *pass = new QTableWidgetItem(QString::number(player->getPass()));
        QTableWidgetItem *defence = new QTableWidgetItem(QString::number(player->getDefence()));
        QTableWidgetItem *steal = new QTableWidgetItem(QString::number(player->getSteal()));
        QTableWidgetItem *block = new QTableWidgetItem(QString::number(player->getBlock()));
        QTableWidgetItem *oRebound = new QTableWidgetItem(QString::number(player->getOffRebound()));
        QTableWidgetItem *dRebound = new QTableWidgetItem(QString::number(player->getDefRebound()));
        QTableWidgetItem *speed = new QTableWidgetItem(QString::number(player->getSpeed()));
        QTableWidgetItem *freethrow = new QTableWidgetItem(QString::number(player->getFreethrow()));

        ui->oppPlayerRatings->setItem(i, 0, three);
        ui->oppPlayerRatings->setItem(i, 1, mid);
        ui->oppPlayerRatings->setItem(i, 2, close);
        ui->oppPlayerRatings->setItem(i, 3, layup);
        ui->oppPlayerRatings->setItem(i, 4, dunk);
        ui->oppPlayerRatings->setItem(i, 5, pass);
        ui->oppPlayerRatings->setItem(i, 6, defence);
        ui->oppPlayerRatings->setItem(i, 7, steal);
        ui->oppPlayerRatings->setItem(i, 8, block);
        ui->oppPlayerRatings->setItem(i, 9, oRebound);
        ui->oppPlayerRatings->setItem(i, 10, dRebound);
        ui->oppPlayerRatings->setItem(i, 11, speed);
        ui->oppPlayerRatings->setItem(i, 12, freethrow);
    }
}

/** Updates the players loaded in the GUI */
void MatchScreen::updatePlayers()
{
    initPlayers();
    initOppositionPlayers(oppositionTeam);
}

//========================================
// Statistics
//========================================

/** Loads the stats of each players in the GUI */
void MatchScreen::loadStats()
{
    vector<QString> header = {"MP", "Pts", "Ast", "Reb", "FGA", "FGM", "FGPC", "Blk", "Stl"};
    //add the headings to the top of the table
    for(int i = 0; i < header.size(); i++)
    {
        ui->statsWidget->setItem(0, i, new QTableWidgetItem(header[i]));
        ui->oppStats->setItem(0, i, new QTableWidgetItem(header[i]));
    }

    //loop through the players on the users team
    for(int i = 1; i <= ownTeam->getRosterSize(); i++)
    {
        //get each players statlist
        StatList *playerStats = ownTeam->getPlayer(i)->getStatList();

        //load the stats into the table
        QTableWidgetItem *minutes = new QTableWidgetItem(QString::number(playerStats->getMinutes()));
        QTableWidgetItem *points = new QTableWidgetItem(QString::number(playerStats->getPointsPerGame()));
        QTableWidgetItem *fga = new QTableWidgetItem(QString::number(playerStats->getShots()));
        QTableWidgetItem *fgpc = new QTableWidgetItem(QString::number(playerStats->getShootingPercentage()));
        QTableWidgetItem *ast = new QTableWidgetItem(QString::number(playerStats->getAssists()));
        QTableWidgetItem *reb = new QTableWidgetItem(QString::number(playerStats->getRebounds()));
        QTableWidgetItem *fgm = new QTableWidgetItem(QString::number(playerStats->getFieldGoalsMade()));
        QTableWidgetItem *steal = new QTableWidgetItem(QString::number(playerStats->getSteals()));
        QTableWidgetItem *block = new QTableWidgetItem(QString::number(playerStats->getBlocks()));
        ui->statsWidget->setItem(i, 0, minutes);
        ui->statsWidget->setItem(i, 1, points);
        ui->statsWidget->setItem(i, 2, ast);
        ui->statsWidget->setItem(i, 3, reb);
        ui->statsWidget->setItem(i, 4, fga);
        ui->statsWidget->setItem(i, 5, fgm);
        ui->statsWidget->setItem(i, 6, fgpc);
        ui->statsWidget->setItem(i, 7, block);
        ui->statsWidget->setItem(i, 8, steal);
    }
    //loop through all opposition players on the court
    for(int i = 1; i < 6; i++)
    {
        //get the players statlist
        StatList *playerStats = oppositionTeam->getPlayer(i)->getStatList();

        //load the stats into the table
        QTableWidgetItem *minutes = new QTableWidgetItem(QString::number(playerStats->getMinutes()));
        QTableWidgetItem *points = new QTableWidgetItem(QString::number(playerStats->getPointsPerGame()));
        QTableWidgetItem *fga = new QTableWidgetItem(QString::number(playerStats->getShots()));
        QTableWidgetItem *fgpc = new QTableWidgetItem(QString::number(playerStats->getShootingPercentage()));
        QTableWidgetItem *ast = new QTableWidgetItem(QString::number(playerStats->getAssists()));
        QTableWidgetItem *reb = new QTableWidgetItem(QString::number(playerStats->getRebounds()));
        QTableWidgetItem *fgm = new QTableWidgetItem(QString::number(playerStats->getFieldGoalsMade()));
        QTableWidgetItem *steal = new QTableWidgetItem(QString::number(playerStats->getSteals()));
        QTableWidgetItem *block = new QTableWidgetItem(QString::number(playerStats->getBlocks()));
        ui->oppStats->setItem(i, 0, minutes);
        ui->oppStats->setItem(i, 1, points);
        ui->oppStats->setItem(i, 2, ast);
        ui->oppStats->setItem(i, 3, reb);
        ui->oppStats->setItem(i, 4, fga);
        ui->oppStats->setItem(i, 5, fgm);
        ui->oppStats->setItem(i, 6, fgpc);
        ui->oppStats->setItem(i, 7, block);
        ui->oppStats->setItem(i, 8, steal);
    }
}

/** Used to update the stats in the GUI */
void MatchScreen::updateStat()
{
    /*
    int newStat;
    if(stat  == 0)
    {
        newStat = ownTeam->getPlayer(player)->getStatList()->getPointsPerGame();
    }
    else if(stat == 1)
    {
        newStat = ownTeam->getPlayer(player)->getStatList()->getShootingPercentage();
    }
    else if(stat == 2)
    {
        newStat = ownTeam->getPlayer(player)->getStatList()->getAssists();
    }
    statTable[player][stat]->setText(QString::number(newStat));
    */
    loadStats();
}

//=================================
// Match Updates
//====================================

/** Updates the clock on the scoreboard */
void MatchScreen::updateTime(int time, int shotClock)
{
    ui->clockShot->display(shotClock);
    //calculate minutes and seconds of the time
    ui->clockMinutes->display(time/60);
    ui->clockSeconds->display(time%60);
}

/** Update the score on the scoreboard */
void MatchScreen::updateScore(int scoreOne, int scoreTwo)
{
    ui->scoreOne->display(scoreOne);
    ui->scoreTwo->display(scoreTwo);
}

/** Initializes the graphical court in the GUI*/
void MatchScreen::initCourt()
{
    //clear the scene
    scene->clear();
    //load the court image
    //downloaded from http://www.conceptdraw.com/How-To-Guide/basketball-court-dimensions
    QPixmap courtImage("../court.png");
    scene->addPixmap(courtImage.scaled(700,400, Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    //add the grid lines horizontally and vertically to represent the grid
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

    //Add player graphics for 10 players on the court
    for(int i = 0; i < 10; i++)
    {
        players.push_back(new PlayerGraphic());
        players[i]->setColour(redBrush);
        //load the ellipse and text item from the graphic class
        scene->addItem(players[i]->getPlayer());
        scene->addItem(players[i]->getNumber());
    }

    //load the ball into the scene
    ballCircle = new QGraphicsEllipseItem(0, 0, 10, 10);
    ballCircle->setBrush(*yellowBrush);
    ballCircle->setPen(*blackPen);
    scene->addItem(ballCircle);
}

void MatchScreen::updateCourt(Ball *ball)
{
    int x, y, drawX, drawY, posModX, posModY;
    int ballTeam = ball->getTeam(), ballPos = ball->getPlayerPosition();
    //loop through team one
    for(int i = 0; i < 5; i++)
    {
        //get the player graphic
        PlayerGraphic *playerGraphic= players[i];
        Player *player = ownTeam->getPlayer(i + 1);

        if(ball->getTeam() == 2)
        {
            x = 6 - player->getPosX();
        }
        else
        {
            x = player->getPosX() + 7;
        }
        y = player->getPosY();

        //random position in each grid space is calculated so its not all uniform
        posModX = rand()%20;
        posModY = rand()%20;
        //calculate the x and y position in the court
        drawX = (x * 50) + posModX;
        drawY = (y * 50) + posModY;

        //set the number, position and colour
        playerGraphic->setNumber(player->getNumber());
        playerGraphic->setPos(drawX, drawY);
        playerGraphic->setColour(redBrush);

        //draw the ball on the player if they are in possession
        if(ballTeam == player->getTeam() && ballPos == i + 1)
        {
            if(ballTeam == 1)
            {
                ballCircle->setPos(drawX + 20, drawY + 10);
            }
            else
            {
                ballCircle->setPos(drawX, drawY + 10);
            }
        }
    }

    //loop through team two
    for(int i = 1; i < 6; i++)
    {
        //get the player graphic
        PlayerGraphic *playerGraphic= players[i + 4];
        Player *player = oppositionTeam->getPlayer(i);
        if(ball->getTeam() == 2)
        {
            x = 6 - player->getPosX();
        }
        else
        {
            x = player->getPosX() + 7;
        }
        y = player->getPosY();

        //random position in each grid space is calculated so its not all uniform
        posModX = rand()%20;
        posModY = rand()%20;
        //calculate the x and y position in the court
        drawX = (x * 50) + posModX;
        drawY = (y * 50) + posModY;

        //set the number, position and colour
        playerGraphic->setNumber(player->getNumber());
        playerGraphic->setPos(drawX, drawY);
        playerGraphic->setColour(blueBrush);

        //draw the ball on the player if they are in possession
        if(ballTeam == player->getTeam() && ballPos == i)
        {
            if(ballTeam == 1)
            {
                ballCircle->setPos(drawX + 20, drawY + 10);
            }
            else
            {
                ballCircle->setPos(drawX, drawY + 10);
            }
        }
    }
}

/** Update the commentary on the screen */
void MatchScreen::updateCommentary(int eventType, Player *p, Player *p2)
{
    //call the commentary class and get a new commentary phrase
    ui->commentary->setText(QString::fromStdString(commentary.getCommentary(eventType, p, p2)));
}

//==========================
// Tactic Slots
//==========================
/*  There a number of Qt slots below. These handle various events in the
 * match screen such as subbing, changing position, strategies. Each element
 * has its own slot.
 */
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

    if(swapIndexOne < 6)
    {
        emit changeStrategy(swapIndexOne, boxes[swapIndexOne][1]->currentIndex());
        emit changePosition(swapIndexOne, boxes[swapIndexOne][0]->currentIndex());
    }
    else if(swapIndexTwo < 6)
    {
        emit changeStrategy(swapIndexTwo, boxes[swapIndexTwo][1]->currentIndex());
        emit changePosition(swapIndexTwo, boxes[swapIndexTwo][0]->currentIndex());
    }
}

void MatchScreen::on_swapPlayerOne_currentIndexChanged(int index)
{
    swapIndexOne = index + 1;
}

void MatchScreen::on_swapPlayerTwo_currentIndexChanged(int index)
{
    swapIndexTwo = index + 1;
}

void MatchScreen::on_defenceType_currentIndexChanged(int index)
{
    emit changeDefenceType(index);
    ui->defenceType_2->setCurrentIndex(index);
}

void MatchScreen::on_defenceType_2_currentIndexChanged(int index)
{
    emit changeDefenceType(index);
    ui->defenceType->setCurrentIndex(index);
}


void MatchScreen::on_matchupOne_currentIndexChanged(int index)
{
    emit changeDefenceMatchup(1, index + 1);
}

void MatchScreen::on_matchupTwo_currentIndexChanged(int index)
{
    emit changeDefenceMatchup(2, index + 1);
}

void MatchScreen::on_matchupThree_currentIndexChanged(int index)
{
    emit changeDefenceMatchup(3, index + 1);
}

void MatchScreen::on_matchupFour_currentIndexChanged(int index)
{
    emit changeDefenceMatchup(4, index + 1);
}

void MatchScreen::on_matchupFive_currentIndexChanged(int index)
{
    emit changeDefenceMatchup(5, index + 1);
}

void MatchScreen::on_defenceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MatchScreen::on_defenceSettingOne_currentIndexChanged(int index)
{
    emit changeDefenceSetting(1, index + 1);
}

void MatchScreen::on_defenceSettingTwo_currentIndexChanged(int index)
{
    emit changeDefenceSetting(2, index + 1);
}

void MatchScreen::on_defenceSettingThree_currentIndexChanged(int index)
{
    emit changeDefenceSetting(3, index + 1);
}

void MatchScreen::on_defenceSettingFour_currentIndexChanged(int index)
{
    emit changeDefenceSetting(4, index + 1);
}

void MatchScreen::on_defenceSettingFive_currentIndexChanged(int index)
{
    emit changeDefenceSetting(5, index + 1);
}

void MatchScreen::on_finishGame_clicked()
{
    emit changeSimSpeed(4);
}
