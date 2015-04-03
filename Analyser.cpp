#include "Analyser.h"

/** Analyser Constructor */
Analyser::Analyser()
{
    //init data to 0
    for(int i = 0; i < 25; i++)
    {
        shotMap[i] = 0;
    }

    for(int i = 1; i < 12; i++)
    {
        decisionMap[i] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    }
}

/** Add a new deicision for a given position*/
void Analyser::addDecision(int pos, int decision)
{
    decisionMap[pos][decision]++;
}

/** Add a shot at a certain time */
void Analyser::addShot(int time)
{
    shotMap[time]++;
}

/** write the data to a csv file */
void Analyser::writeToFile()
{
    std::ofstream outfile;

    //open shot file
      outfile.open("../shots.csv", std::ios_base::app);

      //output the count for each shot time
      for(int i = 24; i >= 0; i--)
      {
          outfile << shotMap[i] << ",";
      }
     outfile << std::endl;

     outfile.close();

    //open decisions file
     outfile.open("../decisions.csv", std::ios_base::app);

     //loop through each player and decision
     for(int i = 1; i < 11; i++)
     {
         for(int j = 0; j < 15; j++)
         {
             //output decision count to file
             outfile << decisionMap[i][j] << ",";
         }
         outfile << std::endl;
     }

    outfile.close();
}
