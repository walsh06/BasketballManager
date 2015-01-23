#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run()
{
    Team *teamOne = new Team("Spurs");
    Team *teamTwo = new Team("Pacers");
    receiver = new MatchReceiver(teamOne, ui->MatchWidget);
    match = new Match(ui->MatchWidget, teamOne, teamTwo);
    connect(ui->MatchWidget, SIGNAL(startGame()), this, SLOT(startGame()));

}

void MainWindow::startGame()
{
    match->sim();
}
