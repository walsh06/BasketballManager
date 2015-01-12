#include <iostream>
#include "Match.h"
#include "MainWindow.h"
#include <time.h>
#include <stdlib.h>

#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    srand(time(NULL));

    for(int i = 1; i < 2; i++)
    {
       Match m;

       m.sim();
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

