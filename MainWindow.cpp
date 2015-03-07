#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    readTeams();
    connect(ui->MatchWidget, SIGNAL(startGame()), this, SLOT(startGame()));

    for(auto &teamName: teamNames)
    {
        ui->teamOneBox->addItem(QString::fromStdString(teamName));
        ui->teamTwoBox->addItem(QString::fromStdString(teamName));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run()
{


}

void MainWindow::startGame()
{
    match->sim();
    loadStatsPostGame(match->getTeamOne(), match->getTeamTwo(), match->getScore()[0], match->getScore()[1]);
    ui->stackedWidget->setCurrentIndex(3);
}

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

void MainWindow::on_playMatch_clicked()
{
    Team *teamOne = new Team(ui->teamOneBox->currentText().toStdString(), true);
    Team *teamTwo = new Team(ui->teamTwoBox->currentText().toStdString());
    receiver = new MatchReceiver(teamOne, ui->MatchWidget);
    match = new Match(teamOne, teamTwo, ui->MatchWidget);
    match->setSimSpeed(1000);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_runSims_clicked()
{
    int simCount = ui->numSims->value();
    ui->simProgress->setMaximum(simCount);

    for(int i = 0; i < simCount; i++)
    {
        ui->simProgress->setValue(i);
        Team teamOne(ui->teamOneBox->currentText().toStdString());
        Team teamTwo(ui->teamTwoBox->currentText().toStdString());
        Match match(&teamOne, &teamTwo);
        match.setSimSpeed(0);
        match.sim();
        string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        match.writeMatchStats(filename);
    }
    ui->simProgress->setValue(simCount);

}

void MainWindow::on_league_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::loadStatsPostGame(Team *teamOne, Team *teamTwo, int teamOneScore, int teamTwoScore)
{
    ui->ScoreOne->display(teamOneScore);
    ui->ScoreTwo->display(teamTwoScore);

    vector<QString> header = {"MP", "Pts", "Ast", "Reb", "FGA", "FGM", "FGPC", "Blk", "Stl"};
    for(int i = 0; i < header.size(); i++)
    {
        ui->statsOne->setItem(0, i, new QTableWidgetItem(header[i]));
        ui->statsTwo->setItem(0, i, new QTableWidgetItem(header[i]));
    }

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

void MainWindow::on_leaveGame_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
