#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Match.h"
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
    Match m(ui->MatchWidget);

    m.sim();
}
