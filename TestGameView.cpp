#include "TestGameView.h"

TestGameView::TestGameView()
{
}


void TestGameView::updateCommentary(int type, Player *p)
{
   switch(type)
   {

       case 1: printValue("Shoot 3", p->getNumber()); break;
       case 2: printValue("Score Mid", p->getNumber()); break;
       case 3: printValue("Score Close", p->getNumber()); break;
       case 4: printValue("Score Dunk", p->getNumber()); break;
       case 5: printValue("Score Layup", p->getNumber()); break;
       case 6: printValue("Assisted Score", p->getNumber()); break;
       case 7: printValue("Foul", p->getNumber()); break;
       case 8: printValue("Offensive Rebound", p->getNumber()); break;
       case 9: printValue("Defensive Rebound", p->getNumber()); break;
       case 10: printValue("Score free throw", p->getNumber()); break;
       case 11: printValue("Miss free throw", p->getNumber()); break;
       case 12: printValue("Miss shot", p->getNumber()); break;
   }
}

void TestGameView::updateTime(int time, int shotClock)
{
    std::cout << "TIME: " << time/60 <<":"<< time%60 << " Shotclock: " << shotClock << std::endl;
}

void TestGameView::printValue(std::string valueName, int value)
{
    std::cout << valueName << ": " << value << std::endl;
}
