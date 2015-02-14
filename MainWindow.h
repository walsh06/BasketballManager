#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Match.h"
#include "MatchReceiver.h"

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

private slots:
    void startGame();
    void on_playMatch_clicked();
    void on_runSims_clicked();
};

#endif // MAINWINDOW_H
