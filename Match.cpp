#include "Match.h"

Match::Match()
{
    teamOne = new Team();
}

void Match::sim()
{
    int shotClock = 0;
    ball.setPlayerNumber(1);
    for(shotClock =24; shotClock >= 0; shotClock--)
    {
        cout << "TIME: " << shotClock << endl;
        cout << "Ball: " << ball.getPlayerNumber() << endl;
        for(int j =1; j < 6; j++)
        {
            Player *p = teamOne->getPlayer(j);
            if(p->getNumber() == ball.getPlayerNumber())
            {
                withBall(p, shotClock);
            }
            else
            {
                move(p);
            }
        }
        printCourt();
    }

}

//================================
// Player Actions
//================================

void Match::move(Player* p)
{
    int x = p->getPosX(), y = p->getPosY();
    p->getPosValue(x, y);

    int map[9];
    int count = 0, total = 0;

    for(int i = y - 1; i <= y + 1; i++)
    {
        for(int j = x - 1; j <= x + 1; j++)
        {
            if(i < 0 || i >= 7)
            {
                map[count] = 0;
            }
            else if(j < 0 || j >= 8)
            {
                map[count] = 0;
            }
            else
            {
                int posValue = p->getPosValue(i, j);
                total += posValue;
                map[count] = posValue;
            }
            count++;
        }
    }


    p->movePlayer(getRandomAction(map, 9, total));
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
        p->getPosValue(x, y);
        //move 0-8, shoot 9, pass 10-13
        int map[14];
        int count = 0, total = 0;

        for(int i = y - 1; i <= y + 1; i++)
        {
            for(int j = x - 1; j <= x + 1; j++)
            {
                if(i < 0 || i >= 7)
                {
                    map[count] = 0;
                }
                else if(j < 0 || j >= 8)
                {
                    map[count] = 0;
                }
                else
                {
                    int posValue = p->getPosValue(i, j);
                    total += posValue;
                    map[count] = posValue;
                }
                count++;
            }
        }

        int posValue = p->getPosValue() + (24 - shotClock) ;
        total += posValue;
        map[count] = posValue;
        count++;

        vector<Player*> otherPlayers = teamOne->getOtherPlayers(p->getNumber());

        for(auto &player: otherPlayers)
        {
            int posValue = player->getPosValue();
            total += posValue;
            map[count] = posValue;
            count++;
        }

        int action  = getRandomAction(map, 14, total);
        cout << "Shot Chance: " << map[9] << endl;
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
// Player Actions Results
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
    }
}

void Match::pass(Player* p, Player* teamMate)
{
    cout << "Pass: " << teamMate->getNumber() << endl;
    ball.setPlayerNumber(teamMate->getNumber());
}

void Match::rebound()
{
    map<int, int> players;
    int total;
    //int randY = (rand() % 4) + 2;
    //int randX = rand() % 3;

    for(int i =1; i < 6; i++)
    {
        Player p = *teamOne->getPlayer(i);
        int posX = p.getPosX, posY = p.getPosY();
        if(posX() > 1 && posX() < 6 && posY() >= 0 && posY < 3)
        {
            if(p.getTeam() == ball->getTeam())
            {
                total+= p.getOffRebound()
                players[p.getNumber()] = total;

            }
            else
            {
                players[p.getNumber()] = p.getDefRebound();
            }
        }
    }

    if(players.size() == 0)
    {

    }
    else if(players.size() == 1)
    {
        ball.setPlayerNumber(players[0].getNumber());
    }
    else
    {

    }
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
        halfCourt[p->getPosY()][p->getPosX()] = j;//(char)(p->getNumber());
    }

    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 7; j++)
            {
               cout << halfCourt[i][j] << " ";
            }
            cout << endl;
        }
    cout << endl;

}
