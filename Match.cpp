#include "Match.h"

Match::Match()
{
    teamOne = new Team();
    teamOne->setTeam(1);
    teamTwo = new Team();
    teamTwo->setTeam(2);
}

void Match::sim()
{
    int shotClock = 0;
    ball.setPlayerPosition(1);
    for(shotClock =24; shotClock >= 0; shotClock--)
    {
        cout << "TIME: " << shotClock << endl;
        cout << "Ball: " << ball.getPlayerPosition() << endl;
        for(int j =1; j < 6; j++)
        {
            Player *p = teamOne->getPlayer(j);
            if(p->getNumber() == ball.getPlayerPosition())
            {
                withBall(p, shotClock);
            }
            else
            {
                move(p);
            }
        }
        for(int j = 1; j < 6; j++)
        {
            Player *p = teamTwo->getPlayer(j);
            moveDefence(p);
        }
        printCourt();
    }

}

//================================
// Player Offense Actions
//================================

void Match::move(Player* p)
{
    ProbabilityVector probs(9);
    int x = p->getPosX(), y = p->getPosY();

    for(int i = y - 1; i <= y + 1; i++)
    {
        for(int j = x - 1; j <= x + 1; j++)
        {
            if(i < 0 || i >= 7)
            {
                probs.addProbability(0);
            }
            else if(j < 0 || j >= 8)
            {
                probs.addProbability(0);
            }
            else
            {
                probs.addProbability(p->getPosValue(i, j));
            }
        }
    }

    p->movePlayer(probs.getRandomResult());
}

void Match::withBall(Player* p, int shotClock)
{
    if(shotClock == 0)
    {
        shoot(p);
    }
    else
    {
        int x = p->getPosX(), y = p->getPosY();
        //move 0-8, shoot 9, pass 10-13
        ProbabilityVector probs(14);


        for(int i = y - 1; i <= y + 1; i++)
        {
            for(int j = x - 1; j <= x + 1; j++)
            {
                if(i < 0 || i >= 7)
                {
                    probs.addProbability(0);
                }
                else if(j < 0 || j >= 8)
                {
                   probs.addProbability(0);
                }
                else
                {
                    probs.addProbability(p->getPosValue(i, j));
                }
            }
        }

        int posValue = p->getPosValue() + (24 - shotClock) ;
        probs.addProbability(posValue);

        vector<Player*> otherPlayers = teamOne->getOtherPlayers(p->getNumber());

        for(auto &player: otherPlayers)
        {
            int posValue = player->getPosValue();
            probs.addProbability(posValue);
        }
        probs.printVector();
        int action  = probs.getRandomResult();

        if(action < 9)
        {
            cout << "Move: " << action << endl;
            p->movePlayer(action);
        }
        else if(action == 9)
        {
            shoot(p);
        }
        else
        {
            pass(p, otherPlayers[action - 10]);
        }
    }

}

int Match::getRandomAction(int arr[], int size, int total)
{
    int randomNum = rand() % total, currentTotal = 0, result = -1;
    for(int i =0; i < size; i++)
    {
        currentTotal += arr[i];
        if(currentTotal > randomNum)
        {
            result = i;
            break;
        }
    }

    return result;
}
//==============================



//================================
// Player Offense Actions Results
//================================

void Match::shoot(Player* p)
{
    int range = p->getRange();
    if(range == 1)
    {

    }
    else if(range == 2)
    {
        shootClose(p);
    }
    else if(range == 3)
    {
        shootMedium(p);
    }
    else if(range == 4)
    {
        shootThree(p);
    }
}

void Match::shootClose(Player* p)
{
    int shotRand = rand() % 43;
    int shot = p->getCloseShot();

    if(shotRand < shot)
    {
       cout << "SCORE Close" << endl;
    }
    else
    {
        cout << "MISS Close" << endl;
        rebound();
    }
}

void Match::shootMedium(Player* p)
{
    int shotRand = rand() % 45;
    int shot = p->getMediumShot();

    if(shotRand < shot)
    {
       cout << "SCORE Mid" << endl;
    }
    else
    {
        cout << "MISS Mid" << endl;
        rebound();
    }
}

void Match::shootThree(Player *p)
{
    int shotRand = rand() % 40;
    int shot;
    if(p->getPosX() == 6)
    {
        shot = p->getThreeShot() / 2;
    }
    else
    {
        shot = p->getThreeShot();
    }

    if(shotRand < shot)
    {
       cout << "SCORE 3" << endl;
    }
    else
    {
        cout << "MISS 3" << endl;
        rebound();
    }
}

void Match::pass(Player* p, Player* teamMate)
{
    cout << "Pass: " << teamMate->getNumber() << endl;
    ball.setPlayerPosition(teamMate->getNumber());
}

void Match::rebound()
{
    ProbabilityVector probs(10);
    int playerNumbers[10];
    int count = 0, reboundRange = 2;

    do{
        for(int i =1; i < 6; i++)
        {
            Player p = *teamOne->getPlayer(i);
            int range = p.getRange();
            if(range <= reboundRange)
            {
                if(p.getTeam() == ball.getTeam())
                {
                    probs.addProbability(p.getOffRebound());
                    playerNumbers[count] = p.getNumber();
                    count++;
                }
                else
                {
                    probs.addProbability(p.getDefRebound() * 3);
                    playerNumbers[count] = p.getNumber();
                    count++;
                }
            }
        }

        if(count == 1)
        {
             ball.setPlayerPosition(playerNumbers[0]);
             cout << "Rebound: " << playerNumbers[0] << endl;
        }
        else if(count > 1)
        {
             int result = probs.getRandomResult();

             ball.setPlayerPosition(playerNumbers[result]);
             cout << "Rebound: " << playerNumbers[result] << endl;
        }
        else
        {
            reboundRange++;
        }

    }while(count == 0);
}

//==============================

//================================
// Player Defense Actions
//================================

void Match::moveDefence(Player *p)
{
    //get the defensive matchup of the player
    int matchup = teamTwo->getMatchup(*p);
    Player opposition = *teamOne->getPlayer(matchup);

    //play tight if their matchup has the ball
    //play tight if their matchup is close to the basket
    //play loose if farther out
    if(ball.getPlayerPosition() == matchup)
    {
        moveDefenceTight(p, opposition);
    }
    else if(opposition.getRange() == 1 || opposition.getRange() == 2)
    {
        moveDefenceTight(p, opposition);
    }
    else
    {
        moveDefenceLoose(p, opposition);
    }
}

void Match::moveDefenceLoose(Player *p, Player opposition)
{
    //get player and opposition positions
    int posX = p->getPosX(), posY = p->getPosY(), oppPosX = opposition.getPosX(), oppPosY = opposition.getPosY();

    if(oppPosX < 3)
    {
        if(oppPosY < 2)
        {
            oppPosY++;
        }
        else
        {
            oppPosY--;
        }
    }
    else
    {
        if(oppPosY < 2)
        {
            oppPosY++;
            oppPosX--;
        }
        else if(oppPosY > 5)
        {
            oppPosY--;
            oppPosX--;
        }
        else
        {
            oppPosX--;
        }
    }

    int moveDirection;
    if(posY < oppPosY)
    {
        if(posX < oppPosX)
        {
            moveDirection = 8;
        }
        else if(posX > oppPosX)
        {
            moveDirection = 6;
        }
        else
        {
            moveDirection = 7;
        }
    }
    else if(posY > oppPosY)
    {
        if(posX < oppPosX)
        {
            moveDirection = 2;
        }
        else if(posX > oppPosX)
        {
            moveDirection = 0;
        }
        else
        {
            moveDirection = 1;
        }
    }
    else
    {
        if(posX < oppPosX)
        {
            moveDirection = 5;
        }
        else if(posX > oppPosX)
        {
            moveDirection = 3;
        }
        else
        {
            moveDirection = 4;
        }
    }
    p->movePlayer(moveDirection);
}

void Match::moveDefenceTight(Player* p, Player opposition)
{
    int posX = p->getPosX(), posY = p->getPosY(), oppPosX = opposition.getPosX(), oppPosY = opposition.getPosY();
    int moveDirection;
    if(posY < oppPosY)
    {
        if(posX < oppPosX)
        {
            moveDirection = 8;
        }
        else if(posX > oppPosX)
        {
            moveDirection = 6;
        }
        else
        {
            moveDirection = 7;
        }
    }
    else if(posY > oppPosY)
    {
        if(posX < oppPosX)
        {
            moveDirection = 2;
        }
        else if(posX > oppPosX)
        {
            moveDirection = 0;
        }
        else
        {
            moveDirection = 1;
        }
    }
    else
    {
        if(posX < oppPosX)
        {
            moveDirection = 5;
        }
        else if(posX > oppPosX)
        {
            moveDirection = 3;
        }
        else
        {
            moveDirection = 4;
        }
    }
    p->movePlayer(moveDirection);
}


//==============================

void Match::printCourt()
{
    int halfCourt[8][7];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            halfCourt[i][j] = 0;
        }
    }

    for(int j =1; j < 6; j++)
    {
        Player *p = teamOne->getPlayer(j);
        cout << j << " " << p->getPosY() << " " << p->getPosX() << endl;
        halfCourt[p->getPosY()][p->getPosX()] = j+10;//(char)(p->getNumber());
    }

    for(int j =1; j < 6; j++)
    {
        Player *p = teamTwo->getPlayer(j);
        cout << j << " " << p->getPosY() << " " << p->getPosX() << endl;
        halfCourt[p->getPosY()][p->getPosX()] = j+20;//(char)(p->getNumber());
    }

    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 7; j++)
            {
               //cout << halfCourt[i][j] << "  ";
               printf("%02i ", halfCourt[i][j]);
            }
            cout << endl;
        }
    cout << endl;

}
