#include <iostream>
#include "Match.h"
#include "MainWindow.h"
#include <time.h>
#include <stdlib.h>

#include <QApplication>
#include <QCoreApplication>
#include <QFile>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleFile("../BasketballManager/darkorange.stylesheet.txt");
    styleFile.open(QFile::ReadOnly);
    QByteArray bytes = styleFile.readAll();
    QApplication *app = (QApplication*)QApplication::instance();
    app->setStyleSheet(bytes);


    MainWindow w;
    w.show();
    w.run();
    srand(time(NULL));

    for(int i = 1; i < 30; i++)
    {
       //Match m;

       //m.sim();
        //string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
       // m.writeMatchStats(filename);
    }

    /*
    Match m;

    m.sim();
    //m.writeMatchStats("Game.csv");
    */
    return a.exec();

}

