#include "LeagueScreen.h"
#include "ui_LeagueScreen.h"

LeagueScreen::LeagueScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeagueScreen)
{
    ui->setupUi(this);

    displayNextMatches();
}

LeagueScreen::~LeagueScreen()
{
    delete ui;
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
        resultString = resultString + result;
    }
    ui->previousMatches->setText(QString::fromStdString(resultString));
}

void LeagueScreen::on_simRound_clicked()
{
    on_playLeagueMatch_clicked();
    league.simRound();
    displayResults();
}

void LeagueScreen::on_playLeagueMatch_clicked()
{
    tuple<int, int> matchup = league.getUserMatch();

    LeagueTeam *teamOne = league.getTeam(get<0>(matchup));
    LeagueTeam *teamTwo = league.getTeam(get<1>(matchup));
    receiver = new MatchReceiver(teamOne->getTeam(), ui->MatchWidget);
    match = new Match(ui->MatchWidget, teamOne->getTeam(), teamTwo->getTeam());
    connect(ui->MatchWidget, SIGNAL(startGame()), this, SLOT(startGame()));
    ui->stackedWidget->setCurrentIndex(1);
}

void LeagueScreen::startGame()
{
    match->sim();
}
