#include <iostream>
#include "MainWindow.h"
#include <time.h>
#include <stdlib.h>
#include <gtest/gtest.h>
#include <QApplication>
#include <QCoreApplication>
#include <QFile>

#include "AutomationTesting.h"
using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if(argc == 1)
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

    return a.exec();
    }
    else
    {
        string s = argv[1];
        if(s == "1")
        {
            testing::InitGoogleTest(&argc, argv);
            return RUN_ALL_TESTS();
        }
        else
        {
            AutomationTesting autoSim;
            autoSim.runTests(stoi(s));
        }
    }
}

