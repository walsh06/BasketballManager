#include <iostream>
#include "Match.h"
#include "MainWindow.h"
#include <time.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include "Tournament.h"
#include "League.h"
using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    /*
    QApplication a(argc, argv);
    QFile styleFile("../BasketballManager/darkorange.stylesheet.txt");
    styleFile.open(QFile::ReadOnly);
    QByteArray bytes = styleFile.readAll();
    QApplication *app = (QApplication*)QApplication::instance();
    app->setStyleSheet(bytes);


    MainWindow w;
    w.show();
    w.run();

    return a.exec();

    */
    //l.printResults();
/*
    Tournament t(4);
    for(int i = 0; i < 14; i++)
    {
        t.simRound();
    }
*/
/*
    for(int i = 1; i < 31; i++)
    {
       //Match m;

        m.sim();
        //string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        //m.writeMatchStats(filename);
    }

        Team teamOne("Heat"), teamTwo("Heat");

        Match m(&teamOne, &teamTwo);
       //m.sim();
        //string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
       // m.writeMatchStats(filename);
    }
*/
/*
    Team teamOne("Pacers"), teamTwo("Pacers");
    Match m(&teamOne, &teamTwo);

    m.sim();

    //m.writeMatchStats("Game.csv");
    */

}

