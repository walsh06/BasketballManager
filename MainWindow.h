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
private slots:
    void startGame();
};

#endif // MAINWINDOW_H
