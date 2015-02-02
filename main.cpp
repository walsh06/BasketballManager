#include <iostream>
#include "Match.h"
#include "Tournament.h"
#include <time.h>
#include <stdlib.h>

#include "League.h"
using namespace std;

int main()
{
    srand(time(NULL));
    //l.printResults();

    Tournament t(4);
    for(int i = 0; i < 14; i++)
    {
        t.simRound();
    }
    /*
    for(int i = 1; i < 2; i++)


    for(int i = 1; i < 31; i++)
    {
        Match m;

        m.sim();
        string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        m.writeMatchStats(filename);
    }
*/
    /*
    Match m;

    m.sim();
    //m.writeMatchStats("Game.csv");
    */
    return 0;

}

