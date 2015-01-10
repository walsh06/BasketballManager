#include <iostream>
#include "Match.h"
#include <time.h>
#include <stdlib.h>
using namespace std;

int main()
{
    srand(time(NULL));
    /*
    string filenames[] = {"Game1.csv", "Game2.csv", "Game3.csv"};
    for(int i = 0; i < 3; i++)
    {
        Match m;

        m.sim(filenames[i]);
    }
    */
    Match m;

    m.sim();
    //m.writeMatchStats("Game.csv");
    return 0;

}

