#include "LeagueScreen.h"
#include "ui_LeagueScreen.h"

LeagueScreen::LeagueScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeagueScreen)
{
    ui->setupUi(this);

    ui->standings->setRowCount(league.getTeamCount());
    updateDisplays();
}

LeagueScreen::~LeagueScreen()
{
    delete ui;
}

//======================================
// Displays
//======================================

void LeagueScreen::updateDisplays()
{
    displayResults();
    displayNextMatches();
    displayTable();
    displayLeaderboard();
}

void LeagueScreen::displayNextMatches()
{
    vector<tuple<int, int>> matchList = league.getNextRound();
    string matchString;

    for(auto &match :matchList)
    {
        matchString = matchString + league.getTeam(get<0>(match))->getTeam()->getName() + " v "
                    + league.getTeam(get<1>(match))->getTeam()->getName() + "\n";
    }
    ui->nextMatches->setText(QString::fromStdString(matchString));
}

void LeagueScreen::displayResults()
{
    vector<string> results = league.getResults();
    string resultString;

    for(auto &result: results)
    {
        resultString = resultString + result + "\n";
    }
    ui->previousMatches->setText(QString::fromStdString(resultString));
}

void LeagueScreen::displayTable()
{
    vector<LeagueTeam *> teams = league.getStandings();
    for(int i =0; i < teams.size(); i++)
    {
        ui->standings->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(teams[i]->getTeam()->getName())));
        ui->standings->setItem(i, 1, new QTableWidgetItem(QString::number(teams[i]->getGames())));
        ui->standings->setItem(i, 2, new QTableWidgetItem(QString::number(teams[i]->getWins())));
    }
}

void LeagueScreen::displayLeaderboard()
{
    ui->ppgLeader->setText(QString::fromStdString(league.getScoringLeader(1)));
    ui->fgpcLeader->setText(QString::fromStdString(league.getScoringLeader(2)));
    ui->tppcLeader->setText(QString::fromStdString(league.getScoringLeader(3)));
    ui->rebLeader->setText(QString::fromStdString(league.getReboundLeader(1)));
    ui->orebLeader->setText(QString::fromStdString(league.getReboundLeader(2)));
    ui->drebLeader->setText(QString::fromStdString(league.getReboundLeader(3)));
    ui->astLeader->setText(QString::fromStdString(league.getOtherLeader(1)));
    ui->blockLeader->setText(QString::fromStdString(league.getOtherLeader(2)));
    ui->stealLeader->setText(QString::fromStdString(league.getOtherLeader(3)));
}

//=======================================
void LeagueScreen::on_simRound_clicked()
{
    //on_playLeagueMatch_clicked();
    league.simRound();
    updateDisplays();
}

void LeagueScreen::on_playLeagueMatch_clicked()
{
    tuple<int, int> matchup = league.getUserMatch();

    LeagueTeam *teamOne = league.getTeam(get<0>(matchup));
    LeagueTeam *teamTwo = league.getTeam(get<1>(matchup));
    receiver = new MatchReceiver(teamOne->getTeam(), ui->MatchWidget);
    match = new Match(teamOne->getTeam(), teamTwo->getTeam(), ui->MatchWidget);
    connect(ui->MatchWidget, SIGNAL(startGame()), this, SLOT(startGame()));
    ui->stackedWidget->setCurrentIndex(1);
}

void LeagueScreen::startGame()
{
    match->sim();
    int scoreHome = match->getScore()[0], scoreAway = match->getScore()[1];
    tuple<int, int> matchup = league.getUserMatch();
    LeagueTeam *teamOne = league.getTeam(get<0>(matchup));
    LeagueTeam *teamTwo = league.getTeam(get<1>(matchup));
    if(scoreHome > scoreAway)
    {
        teamOne->addWin();
        teamTwo->addGame();
    }
    else
    {
        teamTwo->addWin();
        teamOne->addGame();
    }
    ui->previousMatches->setText(QString::fromStdString(to_string(get<0>(matchup)) + " " + to_string(scoreHome) +
                                                        "-" + to_string(scoreAway) +" "+to_string(get<1>(matchup))));

    loadStatsPostGame(teamOne->getTeam(), teamTwo->getTeam());
    ui->stackedWidget->setCurrentIndex(2);
}

//=================================
//Post Game
//==================================

void LeagueScreen::loadStatsPostGame(Team *teamOne, Team *teamTwo)
{
    vector<QString> header = {"MP", "Pts", "Ast", "Reb", "FGA", "FGM", "FGPC", "Blk", "Stl"};
    for(int i = 0; i < header.size(); i++)
    {
        ui->statsOne->setItem(0, i, new QTableWidgetItem(header[i]));
        ui->statsTwo->setItem(0, i, new QTableWidgetItem(header[i]));
    }

    for(int i = 1; i < 11; i++)
    {
        StatList *playerStats = teamOne->getPlayer(i)->getStatList();

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

    for(int i = 1; i < 11; i++)
    {
        StatList *playerStats = teamTwo->getPlayer(i)->getStatList();

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

void LeagueScreen::on_leaveGame_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    league.removeUserMatch();
}
