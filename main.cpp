#include <iostream>
#include "Match.h"
#include <time.h>
#include <stdlib.h>
using namespace std;

int main()
{
    srand(time(NULL));

    for(int i = 1; i < 30; i++)
    {
        Match m;

        m.sim();
        string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        m.writeMatchStats(filename);
    }

    /*
    Match m;

    m.sim();
    //m.writeMatchStats("Game.csv");
    */
    return 0;

}

