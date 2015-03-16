#include "Analyser.h"

Analyser::Analyser()
{
    for(int i = 0; i < 25; i++)
    {
        shotMap[i] = 0;
    }

    for(int i = 1; i < 11; i++)
    {
        decisionMap[i] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    }
}

void Analyser::addDecision(int pos, int decision)
{
    decisionMap[pos][decision]++;
}

void Analyser::addShot(int time)
{
    shotMap[time]++;
}

void Analyser::writeToFile()
{
    std::ofstream outfile;

      outfile.open("Shots.csv", std::ios_base::app);
      outfile << "pos,";

      for(int i = 0; i < 25; i++)
      {
          outfile << shotMap[i] << ",";
      }
     outfile << std::endl;

     outfile.close();

     outfile.open("decisions.csv", std::ios_base::app);
     outfile << "pos,";

     for(int i = 1; i < 11; i++)
     {
         for(int j = 0; j < 15; j++)
         {
             outfile << decisionMap[i][j] << ",";
         }
         outfile << std::endl;
     }

    outfile.close();

}
