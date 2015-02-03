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
    for(int i = 1; i < 31; i++)
    {
        Team teamOne("Heat"), teamTwo("Heat");

        Match m(&teamOne, &teamTwo);

        m.sim();
        string filename = string("../stats/Game") + string(to_string(i)) + string(".csv");
        m.writeMatchStats(filename);
    }
*/
    /*
    Team teamOne("Spurs"), teamTwo("Heat");
    Match m(&teamOne, &teamTwo);

    m.sim();
*/
    return 0;

}

