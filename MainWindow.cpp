#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PlayerStrategyDynamic.h"
#include "PlayerStrategyLearning.h"

/** MainWindow Constructor */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    ui->learnWidget->setVisible(false);

    readTeams();
    connect(ui->MatchWidget, SIGNAL(startGame()), this, SLOT(startGame()));

    //load the team names into the combo boxes
    for(auto &teamName: teamNames)
    {
        ui->teamOneBox->addItem(QString::fromStdString(teamName));
        ui->teamTwoBox->addItem(QString::fromStdString(teamName));
    }
}

/** MainWindow Destructor */
MainWindow::~MainWindow()
{
    delete ui;
}

/** Slot to start a game */
void MainWindow::startGame()
{
    match->sim();
    loadStatsPostGame(match->getTeamOne(), match->getTeamTwo(), match->getScore()[0], match->getScore()[1]);
    ui->stackedWidget->setCurrentIndex(3);
}

/** Read the team names from xml file*/
void MainWindow::readTeams()
{
    //open the document
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file("../BasketballManager/gameData/teams.xml");

    //loop through the tree structure created of the xml
    for (pugi::xml_node team: doc.child("teams"))
    {
       teamNames.push_back(team.first_attribute().value());
    }
}

/** Slot to start a new game */
void MainWindow::on_playMatch_clicked()
{
    //Get the two selected teams
    Team *teamOne = new Team(ui->teamOneBox->currentText().toStdString(), true);
    Team *teamTwo = new Team(ui->teamTwoBox->currentText().toStdString());
    receiver = new MatchReceiver(teamOne, ui->MatchWidget);
    //create the match
    match = new Match(teamOne, teamTwo, ui->MatchWidget);
    //set the sim speed and change screen
    match->setSimSpeed(1000);
    ui->stackedWidget->setCurrentIndex(0);
}

/** Slot to run a large number of simulations */
void MainWindow::on_runSims_clicked()
{
    //get the number of sims to run
    int simCount = ui->numSims->value();
    ui->simProgress->setMaximum(simCount);

    for(int i = 0; i < simCount; i++)
    {
        //update progress bar
        ui->simProgress->setValue(i);
        //Create two teams
        Team teamOne(ui->teamOneBox->currentText().toStdString());
        Team teamTwo(ui->teamTwoBox->currentText().toStdString());
        //Create the match
        Match match(&teamOne, &teamTwo);
        //set the sim speed and start sim
        match.setSimSpeed(0);
        match.sim();
        //write the stats to file
        string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        match.writeMatchStats(filename);
    }
    ui->simProgress->setValue(simCount);  
}

/** Open the leagues screen */
void MainWindow::on_league_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

/** Load the post game screen with stats from the two teams */
void MainWindow::loadStatsPostGame(Team *teamOne, Team *teamTwo, int teamOneScore, int teamTwoScore)
{
    ui->ScoreOne->display(teamOneScore);
    ui->ScoreTwo->display(teamTwoScore);

    //set the headings in the table
    vector<QString> header = {"MP", "Pts", "Ast", "Reb", "FGA", "FGM", "FGPC", "Blk", "Stl"};
    for(int i = 0; i < header.size(); i++)
    {
        ui->statsOne->setItem(0, i, new QTableWidgetItem(header[i]));
        ui->statsTwo->setItem(0, i, new QTableWidgetItem(header[i]));
    }

    //Display team one stats
    for(int i = 1; i <= teamOne->getRosterSize(); i++)
    {
        Player *player = teamOne->getPlayer(i);
        StatList *playerStats = player->getStatList();
        ui->playersOne->addItem(QString::number(player->getNumber()) + QString::fromStdString(" " + player->getName()));

        QTableWidgetItem *minutes = new QTableWidgetItem(QString::number(playerStats->getMinutes()));
        QTableWidgetItem *points = new QTableWidgetItem(QString::number(playerStats->getPointsPerGame()));
        QTableWidgetItem *fga = new QTableWidgetItem(QString::number(playerStats->getShots()));
        QTableWidgetItem *fgpc = new QTableWidgetItem(QString::number(playerStats->getShootingPercentage()));
        QTableWidgetItem *ast = new QTableWidgetItem(QString::number(playerStats->getAssists()));
        QTableWidgetItem *reb = new QTableWidgetItem(QString::number(playerStats->getRebounds()));
        QTableWidgetItem *fgm = new QTableWidgetItem(QString::number(playerStats->getFieldGoalsMade()));
        QTableWidgetItem *steal = new QTableWidgetItem(QString::number(playerStats->getSteals()));
        QTableWidgetItem *block = new QTableWidgetItem(QString::number(playerStats->getBlocks()));
        ui->statsOne->setItem(i, 0, minutes);
        ui->statsOne->setItem(i, 1, points);
        ui->statsOne->setItem(i, 2, ast);
        ui->statsOne->setItem(i, 3, reb);
        ui->statsOne->setItem(i, 4, fga);
        ui->statsOne->setItem(i, 5, fgm);
        ui->statsOne->setItem(i, 6, fgpc);
        ui->statsOne->setItem(i, 7, block);
        ui->statsOne->setItem(i, 8, steal);
    }

    //Display team two stats
    for(int i = 1; i <= teamTwo->getRosterSize(); i++)
    {
        Player *player = teamTwo->getPlayer(i);
        StatList *playerStats = player->getStatList();
        ui->playersTwo->addItem(QString::number(player->getNumber()) + QString::fromStdString(" " + player->getName()));

        QTableWidgetItem *minutes = new QTableWidgetItem(QString::number(playerStats->getMinutes()));
        QTableWidgetItem *points = new QTableWidgetItem(QString::number(playerStats->getPointsPerGame()));
        QTableWidgetItem *fga = new QTableWidgetItem(QString::number(playerStats->getShots()));
        QTableWidgetItem *fgpc = new QTableWidgetItem(QString::number(playerStats->getShootingPercentage()));
        QTableWidgetItem *ast = new QTableWidgetItem(QString::number(playerStats->getAssists()));
        QTableWidgetItem *reb = new QTableWidgetItem(QString::number(playerStats->getRebounds()));
        QTableWidgetItem *fgm = new QTableWidgetItem(QString::number(playerStats->getFieldGoalsMade()));
        QTableWidgetItem *steal = new QTableWidgetItem(QString::number(playerStats->getSteals()));
        QTableWidgetItem *block = new QTableWidgetItem(QString::number(playerStats->getBlocks()));
        ui->statsTwo->setItem(i, 0, minutes);
        ui->statsTwo->setItem(i, 1, points);
        ui->statsTwo->setItem(i, 2, ast);
        ui->statsTwo->setItem(i, 3, reb);
        ui->statsTwo->setItem(i, 4, fga);
        ui->statsTwo->setItem(i, 5, fgm);
        ui->statsTwo->setItem(i, 6, fgpc);
        ui->statsTwo->setItem(i, 7, block);
        ui->statsTwo->setItem(i, 8, steal);
    }
}

/** Slot to leave a match and return to main menu */
void MainWindow::on_leaveGame_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/** Close the learning menu */
void MainWindow::on_closeLearning_clicked()
{
    ui->learnWidget->setVisible(false);
}

/** Run learning simulations */
void MainWindow::on_runLearning_clicked()
{
    //get the settings from the menu
    int numMatches = 50;
    int simCount = ui->iterationCount->value();
    int playerPos = ui->playerPos->value();
    ui->simProgress->setMaximum(simCount * numMatches);

    //set the strategy and the learning stats
    PlayerStrategy *dynamicStrategy = new PlayerStrategyDynamic();
    PlayerStrategyLearning learning(ui->thrpa->value(), ui->twopa->value(), ui->ast->value(), ui->orb->value(), ui->games->value());

    //start the simulations
    for(int i = 0; i < simCount; i++)
    {
        //create team one and prepare player for learning
        Team teamOne(ui->teamOneBox->currentText().toStdString());
        teamOne.getPlayer(playerPos)->setLearning(true);
        teamOne.getPlayer(playerPos)->setStrategy(dynamicStrategy);
        Team teamTwo(ui->teamTwoBox->currentText().toStdString());

        //run learning iteration
        for(int j=0; j<numMatches; j++)
        {
            //update progress bar
            ui->simProgress->setValue((i*numMatches) + j);

            //simulate the match
            Match match(&teamOne, &teamTwo);
            match.setSimSpeed(0);
            match.sim();
        }
        //update the strategy after iteration and write to file
        learning.updateStrategy(teamOne.getRoster()[playerPos - 1]);
        learning.writeToFile(teamOne.getRoster()[playerPos - 1]);
    }
    ui->simProgress->setValue(simCount * numMatches);
}

/** Open the learning menu */
void MainWindow::on_openLearning_clicked()
{
    ui->learnWidget->setVisible(true);
}
