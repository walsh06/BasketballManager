#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Match.h"
#include "MatchReceiver.h"

/* Qt class for the main graphical window
 * Manages the main menu of the game and start up
 * game
 */
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void run();

private:
    Ui::MainWindow *ui;
    Match *match;
    MatchReceiver *receiver;
    vector<string> teamNames;

    void readTeams();
    void loadStatsPostGame(Team *teamOne, Team *teamTwo, int teamOneScore, int teamTwoScore);

private slots:
    void startGame();
    void on_playMatch_clicked();
    void on_runSims_clicked();
    void on_league_clicked();
    void on_leaveGame_clicked();
    void on_closeLearning_clicked();
    void on_runLearning_clicked();
    void on_openLearning_clicked();
    void quitLeague();
};

#endif // MAINWINDOW_H
