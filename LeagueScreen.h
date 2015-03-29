#ifndef LEAGUESCREEN_H
#define LEAGUESCREEN_H

#include <QWidget>
#include "League.h"
#include "MatchScreen.h"
#include "MatchReceiver.h"

/* Qt class for displaying the league game mode
 */
namespace Ui {
class LeagueScreen;
}

class LeagueScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LeagueScreen(QWidget *parent = 0);
    ~LeagueScreen();
    void updateDisplays();

private slots:
    void startGame();
    void on_simRound_clicked();
    void on_playLeagueMatch_clicked();

    void on_leaveGame_clicked();

private:
    Ui::LeagueScreen *ui;
    Match *match;
    League league;
    MatchReceiver *receiver;

    void loadStatsPostGame(Team *teamOne, Team *teamTwo, int teamOneScore, int teamTwoScore);
    void displayNextMatches();
    void displayResults();
    void displayTable();
    void displayLeaderboard();
};

#endif // LEAGUESCREEN_H
