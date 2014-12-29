#include "Match.h"

Match::Match()
{
    teamOne = new Team();
    teamOne->setTeam(1);
    teamTwo = new Team();
    teamTwo->setTeam(2);

    teams[0] = teamOne;
    teams[1] = teamTwo;

    ball.setTeam(2);
    setUpRestartInbound();
    score[0] = 0;
    score[1] = 0;
}

void Match::sim()
{
    for(int time = 180; time > 0;)
    {
        cout << "Score: " << score[0] << "-" << score[1] << endl;
        for(shotClock = 24; shotClock >= 0 && time >= 0; shotClock--, time--)
        {
            if(time < 24)
            {
                shotClock = time;
            }
            setOrderOfPlay();
            cout << "TIME: " << time << " Shotclock: " << shotClock << endl;
            cout << "Ball: " << ball.getTeam() << " " << ball.getPlayerPosition() << endl;
            for(auto &player : orderOfPlay)
            {
                if(player->getTeam() == ball.getTeam())
                {
                    if(teams[player->getTeam() - 1]->getPlayerPosition(player->getNumber()) == ball.getPlayerPosition())
                    {
                        if(gameState == INPLAY)
                            withBall(player, shotClock);
                        else if(gameState == INBOUND)
                            passInbound(player);

                        if(shotClock == 0)
                        {
                            break;
                        }
                    }
                    else
                    {
                        move(player);
                    }
                }
                else
                {
                    moveDefence(player);
                }
            }

            printCourt();
        }
    }
    cout << "Score: " << score[0] << "-" << score[1] << endl;

}

void Match::setOrderOfPlay()
{
    orderOfPlay.clear();
    vector<Player *> players;
    map<int, Player*> playersWithSpeed;
    int speedOne, speedTwo;
    for(int j =1; j < 6; j++)
    {
        Player *p1 = teamOne->getPlayer(j);
        Player *p2 = teamTwo->getPlayer(j);
        do
        {
            speedOne = 30 - (p1->getSpeed() + (rand() % 10));
        }while(playersWithSpeed.find(speedOne) != playersWithSpeed.end());
        playersWithSpeed[speedOne] = p1;
        do
        {
            speedTwo = 30 - (p2->getSpeed() + (rand() % 10));
        }while(playersWithSpeed.find(speedTwo) != playersWithSpeed.end());
        playersWithSpeed[speedTwo] = p2;
    }

    std::vector<Player*>::iterator it = orderOfPlay.begin();
    for(auto &player: playersWithSpeed)
    {
        orderOfPlay.push_back(player.second);
    }
}

int Match::getOtherTeam(int team)
{
    if(team == 1) return 1;
    else return 0;
}

void Match::swapSides()
{
    teams[0]->swapSides();
    teams[1]->swapSides();
    ball.changeTeam();
    ball.setPlayerPosition(1);
    shotClock = 0;
}

void Match::setUpRestartInbound()
{
    shotClock = 0;
    teams[0]->swapSides();
    teams[1]->swapSides();
    ball.changeTeam();
    ball.setPlayerPosition(3);

    int team = ball.getTeam();
    teamOne->restartInbound(team);
    teamTwo->restartInbound(team);
    gameState = INBOUND;
}

//================================
// Player Offense Actions
//================================

void Match::move(Player* p)
{
    if(p->getPosX() < 0)
    {
        p->movePlayer(5);
    }
    else
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
}

void Match::withBall(Player* p, int shotClock)
{
    if(shotClock == 0)
    {
        shoot(p);
    }
    else if(p->getPosX() < 0)
    {
        p->movePlayer(5);
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
                if(i < 0 || i > 7)
                {
                    probs.addProbability(0);
                }
                else if(j < 0 || j > 8)
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

        vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());

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

void Match::passInbound(Player *p)
{
    ProbabilityVector probs(14);

    vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());

    for(auto &player: otherPlayers)
    {
        if(player->getPosX() < 0)
        {
            probs.addProbability(10);
        }
        else
        {
            probs.addProbability(0);
        }
    }

    int action  = probs.getRandomResult();
    pass(p, otherPlayers[action]);
    gameState = INPLAY;
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
        shootUnderBasket(p);
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

void Match::shootUnderBasket(Player *p)
{
    int shotRand = rand() % 35;
    int shot = p->getUnderBasketShot(), freeThrows = 0;

    int foulRand = rand() % 5;

    if(foulRand == 0)
    {
        freeThrows = 2;
    }

    if(shotRand < shot)
    {
       cout << "SCORE Under Basket" << endl;
       shotClock = 0;
       score[p->getTeam() - 1]+=2;
       if(freeThrows == 0)
       {
            setUpRestartInbound();
       }
       else
       {
           freeThrows = 1;
       }
    }
    else
    {
        cout << "MISS Under Basket" << endl;
        if(freeThrows == 0)
        {
            block(p);
            rebound();
        }
    }

    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}
void Match::shootClose(Player* p)
{
    int shotRand = rand() % 43;
    int shot = p->getCloseShot(), freeThrows = 0;

    int foulRand = rand() % 5;

    if(foulRand == 0)
    {
        freeThrows = 2;
    }

    if(shotRand < shot)
    {
       cout << "SCORE Close" << endl;
       shotClock = 0;
       score[p->getTeam() - 1]+=2;
       if(freeThrows == 0)
       {
            setUpRestartInbound();
       }
       else
       {
           freeThrows=1;
       }
    }
    else
    {
        cout << "MISS Close" << endl;
        if(freeThrows == 0)
        {
            block(p);
            rebound();
        }
    }

    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}

void Match::shootMedium(Player* p)
{
    int shotRand = rand() % 45;
    int shot = p->getMediumShot(), freeThrows = 0;

    int foulRand = rand() % 5;

    if(foulRand == 0)
    {
        freeThrows = 2;
    }

    if(shotRand < shot)
    {
       cout << "SCORE Mid" << endl;
       shotClock = 0;
       score[p->getTeam() - 1]+=2;
       if(freeThrows == 0)
       {
            setUpRestartInbound();
       }
       else
       {
           freeThrows=1;
       }
    }
    else
    {
        cout << "MISS Mid" << endl;
        if(freeThrows == 0)
        {
            block(p);
            rebound();
        }
    }
    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}

void Match::shootThree(Player *p)
{
    int shotRand = rand() % 43;
    int shot, freeThrows = 0;

    int foulRand = rand() % 5;

    if(foulRand == 0)
    {
        freeThrows = 3;
    }
    if(p->getPosX() == 0)
    {
        shot = p->getThreeShot() / 4;
    }
    else
    {
        shot = p->getThreeShot();
    }

    if(shotRand < shot)
    {
       cout << "SCORE 3" << endl;
       shotClock = 0;
       score[p->getTeam() - 1]+=3;
       if(freeThrows == 0)
       {
        setUpRestartInbound();
       }
       else
       {
           freeThrows=1;
       }
    }
    else
    {
        cout << "MISS 3" << endl;
        if(freeThrows == 0)
        {
            block(p);
            rebound();
        }
    }
    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}

void Match::shootFreeThrow(Player *p, int numOfFreeThrows)
{
    int ft = p->getFreethrow();

    do
    {
        int ftProb = rand() % 22;
        if(ft < ftProb)
        {
            cout << "Free Throw: " << p->getNumber() << endl;
            score[p->getTeam() - 1]++;
            if(numOfFreeThrows == 1)
            {
                setUpRestartInbound();
            }
        }
        else
        {
            cout << "Missed Free Throw: " << p->getNumber() << endl;
            if(numOfFreeThrows == 1)
            {
                rebound();
            }
        }
        numOfFreeThrows--;
    }while(numOfFreeThrows > 0);

}

void Match::pass(Player* p, Player* teamMate)
{
    cout << "Pass: " << teamMate->getNumber() << endl;
    ball.setPlayerPosition(teamMate->getNumber());
}

void Match::rebound()
{
    ProbabilityVector probs(10);
    vector<Player *> players;
    int count = 0, reboundRange = 2;

    do{
        for(auto &player: orderOfPlay)
        {
            Player p = *player;
            int range = p.getRange();
            if(range <= reboundRange)
            {
                if(p.getTeam() == ball.getTeam())
                {
                    probs.addProbability(p.getOffRebound());
                }
                else
                {
                    probs.addProbability(p.getDefRebound() * 3);
                }
                players.push_back(player);
                count++;
            }
        }

        if(count > 0)
        {
            Player *p;
            int pos;
            if( count == 1)
            {
                p = players[0];
            }
            else
            {
                int result = probs.getRandomResult();
                p = players[result];
            }
            pos = teams[p->getTeam() - 1]->getPlayerPosition(p->getNumber());

             ball.setPlayerPosition(pos);
             if(ball.getTeam() == p->getTeam())
             {
                 cout << "Offensive Rebound: " << p->getNumber() << endl;
                shotClock = 0;
             }
             else
             {
                 cout << "Defensive Rebound: " << p->getNumber() << endl;
                 shotClock = 0;
                 swapSides();
             }
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
    int matchup, team = getOtherTeam(p->getTeam());
    //get the defensive matchup of the player

    matchup = teams[p->getTeam() - 1]->getMatchup(*p);
    Player opposition = *teams[team]->getPlayer(matchup);


    //play tight if their matchup has the ball
    //play tight if their matchup is close to the basket
    //play loose if farther out
    if(p->getPosX() < 0)
    {
        p->movePlayer(5);
    }
    else if(ball.getPlayerPosition() == matchup)
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

    if(oppPosX > 3)
    {
        if(oppPosY < 2)
        {
            oppPosY++;
        }
        else if(oppPosY > 5)
        {
            oppPosY--;
        }
    }
    else
    {
        if(oppPosY < 2)
        {
            oppPosY++;
        }
        else if(oppPosY > 5)
        {
            oppPosY--;
        }
        oppPosX++;
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


//================================
// Player Defense Actions Results
//================================

void Match::block(Player *p)
{
    for(int i = 1; i < 6; i++)
    {
        Player opp = *teams[getOtherTeam(p->getTeam())]->getPlayer(i);
        if(opp.getPosX() == p->getPosX() && opp.getPosY() == p->getPosY())
        {
            int block = rand() % 200;

            if(block < opp.getBlock())
            {
                cout << "Block: " << opp.getNumber() << endl;
            }
        }
    }
}

//==============================

void Match::printCourt()
{
    int halfCourt[8][14];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 14; j++)
        {
            halfCourt[i][j] = 0;
        }
    }

    for(int j =1; j < 6; j++)
    {
        Player *p = teamOne->getPlayer(j);
        cout << j << " " << p->getPosY() << " " << p->getPosX() << endl;
        halfCourt[p->getPosY()][p->getPosX() + 7] = j+10;//(char)(p->getNumber());
    }

    for(int j =1; j < 6; j++)
    {
        Player *p = teamTwo->getPlayer(j);
        cout << j << " " << p->getPosY() << " " << p->getPosX() << endl;
        halfCourt[p->getPosY()][p->getPosX() + 7] = j+20;//(char)(p->getNumber());
    }

    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 14; j++)
            {
               //cout << halfCourt[i][j] << "  ";
               printf("%02i ", halfCourt[i][j]);
            }
            cout << endl;
        }
    cout << endl;

}
