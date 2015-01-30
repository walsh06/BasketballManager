#include <iostream>
#include "Match.h"
#include <time.h>
#include <stdlib.h>

#include "League.h"
using namespace std;

int main()
{
    srand(time(NULL));
    League l;
    l.simRound(1);
    //l.printResults();
    l.simRound(2);
    l.simRound(3);
    l.printResults();
    l.printTable();
    /*
    for(int i = 1; i < 2; i++)
    {
        Match m;

        m.sim();
        //string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        //m.writeMatchStats(filename);
    }
*/
    /*
    Match m;

    m.sim();
    //m.writeMatchStats("Game.csv");
    */
    return 0;

}

