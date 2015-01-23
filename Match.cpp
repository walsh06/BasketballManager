#include "Match.h"

int Match::simSpeed = 1000;

Match::Match(MatchScreen *newScreen, Team *teamOne, Team *teamTwo)
{
    this->teamOne = teamOne;
    this->teamOne->setTeam(1);
    this->teamTwo = teamTwo;
    this->teamTwo->setTeam(2);

    teams[0] = this->teamOne;
    teams[1] = this->teamTwo;

    score[0] = 0;
    score[1] = 0;
    assist = make_tuple(new Player(0), 800);

    setOrderOfPlay();
    screen = newScreen;
    screen->initTacticScreen(teamOne);
}

Match::~Match()
{
    delete teamOne;
    delete teamTwo;
}

void Match::sim()
{
    for(int i = 0; i < 4; i++)
    {
        if(i==0)
        {
            jumpBall();
        }
        else if(i == 2 || i == 1)
        {
           int team = getOtherTeam(firstPossession);
           ball.setTeam(team + 1);
           ball.setPlayerPosition(3);
           ball.setPos(-7, 4);

           teamOne->restartInbound(team + 1);
           teamTwo->restartInbound(team + 1);
           gameState = INBOUND;
        }
        else
        {
            int team = firstPossession;
            ball.setTeam(team);
            ball.setPlayerPosition(3);
            ball.setPos(-7, 4);

            teamOne->restartInbound(team);
            teamTwo->restartInbound(team);
            gameState = INBOUND;
        }
        fouls.resetFouls();
        for(time = 720; time > 0;)
        {
            cout << "Score: " << score[0] << "-" << score[1] << endl;
            for(shotClock = 24; shotClock >= 0 && time >= 0; shotClock--, time--)
            {
                if(time < 24 && shotClock == 24)
                {
                    shotClock = time;
                }

                setOrderOfPlay();
                screen->updateTime(time, shotClock);
                cout << "Q" << i+1 << " TIME: " << time << " Shotclock: " << shotClock << endl;
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

                QTime dieTime= QTime::currentTime().addMSecs(Match::simSpeed);
                    while( QTime::currentTime() < dieTime )
                    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

                 screen->updateCourt(orderOfPlay, &ball);

                if(time%60 == 0)
                {
                    teamOne->updateEnergy();
                    teamTwo->updateEnergy();
                }
                //printCourt();
            }
        }
    }

    screen->updateCourt(orderOfPlay, &ball);
    cout << "Score: " << score[0] << "-" << score[1] << endl;

    shotMap.printHeatMap();
}


//===============================
// General Functions
//===============================

void Match::setSimSpeed(int speed)
{
    Match::simSpeed = speed;
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

int Match::getScoreDifference(int team)
{
    return score[getOtherTeam(team)] - score[team];
}

void Match::writeMatchStats(string filename)
{
    vector<Player *> rosterOne = teamOne->getRoster(), rosterTwo = teamTwo->getRoster();
    for(int i = 0; i < 10; i++)
    {
        Player *player = rosterOne[i];
        cout << "Player: " << player->getNumber() << " Team: " << player->getTeam() << endl;
        player->getStatList()->printShootingStats();
        player->getStatList()->printReboundingStats();
        cout << endl;
        player->getStatList()->writeToFile(filename, i + 1);
    }

    for(int i = 0; i < 10; i++)
    {
        Player *player = rosterTwo[i];
        cout << "Player: " << player->getNumber() << " Team: " << player->getTeam() << endl;
        player->getStatList()->printShootingStats();
        player->getStatList()->printReboundingStats();
        cout << endl;
        player->getStatList()->writeToFile(filename,i + 1);
    }
}

//====================================
// Changing Game State
//====================================
void Match::swapSides(int playerNum)
{
    teams[0]->swapSides();
    teams[1]->swapSides();
    ball.changeTeam();
    ball.setPlayerPosition(teams[ball.getTeam() - 1]->getPlayerPosition(playerNum));

    shotClock = 0;
}

void Match::setUpRestartInbound()
{
    shotClock = 0;
    teams[0]->swapSides();
    teams[1]->swapSides();
    ball.changeTeam();
    ball.setPlayerPosition(3);
    ball.setPos(-7, 4);

    int team = ball.getTeam();
    teamOne->restartInbound(team);
    teamTwo->restartInbound(team);
    gameState = INBOUND;
}

void Match::setUpOffensiveInbound()
{
    ball.setPlayerPosition(4);

    int team = ball.getTeam();
    teamOne->offensiveInbound(team);
    teamTwo->offensiveInbound(team);
    gameState = INBOUND;
}

void Match::setUpOwnSideInbound()
{
    ball.setPlayerPosition(4);

    int team = ball.getTeam();
    teamOne->ownSideInbound(team);
    teamTwo->ownSideInbound(team);
    gameState = INBOUND;
}

void Match::jumpBall()
{
    Player* playerOne = teamOne->getPlayer(5), *playerTwo = teamTwo->getPlayer(5);
    teamOne->setUpStartGame(); teamTwo->setUpStartGame();
    printCourt();

    ProbabilityVector jumpVector(2);

    jumpVector.addProbability(playerOne->getDefRebound());
    jumpVector.addProbability(playerTwo->getDefRebound());

    int jumpWinner = jumpVector.getRandomResult();

    ball.setPlayerPosition(1);

    firstPossession = jumpWinner + 1;
    if(jumpWinner == 0)
    {
        ball.setTeam(1);
        ball.setPos(teamOne->getPlayer(1)->getPosX(), teamOne->getPlayer(1)->getPosY());

        cout << "Jump Ball: Team 1" << endl;
    }
    else if(jumpWinner == 1)
    {
        cout << "Jump Ball: Team 2" << endl;
        ball.setPos(teamTwo->getPlayer(1)->getPosX(), teamTwo->getPlayer(1)->getPosY());

        teams[0]->swapSides();
        teams[1]->swapSides();
        ball.setTeam(2);
    }
    gameState = INPLAY ;
    screen->updateCourt(orderOfPlay, &ball);

}
//================================



void Match::updateScore(int team, int points)
{
    score[team]+=points;
    screen->updateScore(score[0], score[1]);
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
                if(i < 0 || i >= 8)
                {
                    probs.addProbability(0);
                }
                else if(j < 0 || j >= 7)
                {
                    probs.addProbability(0);
                }
                else
                {
                    probs.addProbability(p->getPosValue(j, i));
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
        shoot(p, teams[getOtherTeam(p->getTeam())]->getPressure(p->getPosX(), p->getPosY()));
    }
    else if(p->getPosX() < 0)
    {
        p->movePlayer(5);
    }
    else if(p->isDribbleDrive())
    {
        driveBasket(p);
    }
    else
    {
        int x = p->getPosX(), y = p->getPosY(), shotClockFactor = 12;
        //move 0-8, shoot 9, pass 10-13, drive 14
        ProbabilityVector probs(15);
        //=================
        //MOVEMENT
        //=================
        for(int i = y - 1; i <= y + 1; i++)
        {
            for(int j = x - 1; j <= x + 1; j++)
            {
                if(i < 0 || i >= 8)
                {
                    probs.addProbability(0);
                }
                else if(j < 0 || j >= 7)
                {
                   probs.addProbability(0);
                }
                else
                {
                    probs.addProbability(p->getPosValue(j, i));
                }
            }
        }
        //=================
        //SHOOTING
        //=================
        int pressure = teams[getOtherTeam(p->getTeam())]->getPressure(p->getPosX(), p->getPosY());
        int defendersUnderBasket = teams[getOtherTeam(p->getTeam())]->getPlayersUnderBasket();
        int scoreDifference = getScoreDifference(p->getTeam());
        int posValue = (scoreDifference/4);

        if(p->getRange() == 1 && defendersUnderBasket == 0)
        {
            posValue = p->getPosValue() + 100;
        }
        else if(pressure == 0)
        {
            posValue = p->getPosValue() + (shotClockFactor - shotClock) + 100;
        }
        else
        {
            posValue = p->getPosValue() + (shotClockFactor - shotClock) - pressure - (p->getRange() * 1);
        }
        probs.addProbability(posValue);


        //=================
        //PASSING
        //=================
        vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());

        for(auto &player: otherPlayers)
        {
            int posValue = 0;
            vector<int> defenders = getDefendersForPass(getOtherTeam(p->getTeam()), x, y, player->getPosX(), player->getPosY());
            if(player->getPosX() >= 0)
            {
                posValue = player->getPosValue() + (p->getPass() / 4) - abs((x - player->getPosX()) + (y - player->getPosY()));
            }

            if(defenders.size() > 0)
            {
                posValue -= (defenders.size() * 2);
            }
            probs.addProbability(posValue);
        }

        //=================
        //Drive Basket
        //=================
        int value = p->getUnderBasketShot(), underBasket = teams[getOtherTeam(p->getTeam())]->getPlayersUnderBasket();

        if(underBasket == 0)
        {
            value += 10;
        }

        probs.addProbability(value);
        //=================
        ProbabilityVector finalProbabilities = probs + p->getStrategyVector();
        finalProbabilities.printVector();

        int action  = finalProbabilities.getRandomResult();

        if(action < 9)
        {
            cout << "Move: " << action << endl;
            p->movePlayer(action);
        }
        else if(action == 9)
        {
            shoot(p, pressure);
        }
        else if(action == 14)
        {
            p->setDribbleDrive(true);
            driveBasket(p);
        }
        else
        {
            pass(p, otherPlayers[action - 10]);
        }
    }
    ball.setPos(p->getPosX(), p->getPosY());
}

void Match::passInbound(Player *p)
{
    ProbabilityVector probs(14);

    vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());
    bool ownSide = p->getPosX() < 0;
    int x = p->getPosX(), y = p->getPosY(), team = getOtherTeam(p->getTeam());
    for(auto &player: otherPlayers)
    {
        int posValue = 0;

        if(ownSide)
        {
            if(player->getPosX() < 0)
            {
                posValue = 10;
            }
            else
            {
                posValue = 0;
            }
        }
        else
        {
            vector<int> defenders = getDefendersForPass(team, x, y, player->getPosX(), player->getPosY());
            if(player->getPosX() >= 0)
            {
                posValue = player->getPosValue() + (p->getPass() / 4) - abs((x - player->getPosX()) + (y - player->getPosY()));
            }

            if(defenders.size() > 0)
            {
                posValue -= (defenders.size() * 2);
            }
        }
        probs.addProbability(posValue);
    }

    int action  = probs.getRandomResult();
    pass(p, otherPlayers[action]);
    gameState = INPLAY;
}

void Match::driveBasket(Player *p)
{
    int posX = p->getPosX(), posY = p->getPosY();
    if(p->getRange() == 1)
    {
        shoot(p, teams[getOtherTeam(p->getTeam())]->getPressure(posX, posY));
    }
    else
    {
        int move;
        if(posY == 3 || posY == 4)
        {
            move = 5;
        }
        else if(posX == 6 || posX == 5)
        {
            if((3 - posY) < 0)
            {
                move = 1;
            }
            else
            {
                move = 7;
            }
        }
        else
        {
            if((3 - posY) < 0)
            {
                move = 2;
            }
            else
            {
                move = 8;
            }
        }

        for(int i = 1; i < 6; i++)
        {
            Player opp = *teams[getOtherTeam(p->getTeam())]->getPlayer(i);
            if(opp.getPosX() == posX && opp.getPosY() == posY)
            {
                int screenRand = rand() % 50;

                if(screenRand < 25)
                {
                    cout << "Drive Stopped: " << p->getNumber() << " " << opp.getNumber() << endl;
                    move = 4;
                    p->setDribbleDrive(false);
                    break;
                }
                else if(screenRand < 28)
                {
                    cout << "Blocking foul: " << opp.getNumber() << " on " << p->getNumber() << endl;
                    fouls.addFoul(p->getTeam(), time);
                    if(fouls.getTeamBonus(p->getTeam()) == true)
                    {
                        shootFreeThrow(p, 2);
                    }
                    else
                    {
                        setUpOffensiveInbound();
                        if(shotClock < 14)
                        {
                            shotClock = 14;
                        }
                    }
                }
                else if(screenRand == 31)
                {
                    cout << "Offensive foul: " << p->getNumber() << endl;
                    ball.changeTeam();
                    shotClock = 0;
                    setUpOwnSideInbound();
                }
            }
        }
        cout << "Drive: " << move << endl;
        p->movePlayer(move);
    }
}

//==============================

vector<int> Match::getDefendersForPass(int team, int x1, int y1, int x2, int y2)
{
    vector<int> defenders;
    Team *defendingTeam = teams[team];
    float slope;
    if((x2 - x1) == 0)
    {
        slope = 2;
    }
    else
    {
       slope = fabs((y2 - y1)/(x2 - x1));
    }

    if(slope == 1)
    {
        if(x1 > x2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }
        for(int i = x1, j = y1; i <= x2 && j <= y2; i++, j++)
        {
            vector<int> defendersAtPosition = defendingTeam->getPlayersInPosition(i, j);

            if(defendersAtPosition.size() > 0)
            {
                defenders.insert(defenders.end(), defendersAtPosition.begin(),defendersAtPosition.end());
            }
        }
    }
    else
    {
        if(slope > 1)
        {
            swap(x1, y1);
            swap(x2, y2);
        }

        if(x1 > x2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }

        int dx = x2 - x1, dy = y2 - y1, j = y1;
        float diff = dx / 2.0f;
        int step = (y1 < y2) ? 1 : -1;

        for(int i = x1; i <= x2; i++)
        {
            vector<int> defendersAtPosition;
            if(slope > 1)
            {
                defendersAtPosition = defendingTeam->getPlayersInPosition(j, i);
            }
            else
            {
                defendersAtPosition = defendingTeam->getPlayersInPosition(i, j);
            }
            if(defendersAtPosition.size() > 0)
            {
                defenders.insert(defenders.end(), defendersAtPosition.begin(),defendersAtPosition.end());
            }
            diff -= dy;
            if(diff < 0)
            {
                j += step;
                diff += dx;
            }
        }
    }
    return defenders;
}

//================================
// Player Offense Actions Results
//================================

void Match::shoot(Player* p, int pressure)
{
    shotMap.incrementValue(p->getPosX(), p->getPosY());
    screen->updateCommentary(1, p);
    int range = p->getRange();
    if(range == 1)
    {
        shootUnderBasket(p, pressure);
    }
    else if(range == 2)
    {
        shootClose(p, pressure);
    }
    else if(range == 3)
    {
        shootMedium(p, pressure);
    }
    else
    {
        shootThree(p, pressure);
    }
}

void Match::shootUnderBasket(Player *p, int pressure)
{
    int shotRand = rand() % (30 + pressure);
    int shot = p->getUnderBasketShot() , freeThrows = 0;

    int foulRand = rand() % 6;

    if(foulRand == 0)
    {
        freeThrows = 2;
        fouls.addFoul(p->getTeam(), time);
    }

    if(shotRand < shot)
    {
       cout << "SCORE Under Basket" << endl;
       updateScore(p->getTeam() - 1, 2);
       p->getStatList()->addTwoPoints();
       checkAssist();

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
        p->getStatList()->addMiss();

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
void Match::shootClose(Player* p, int pressure)
{
    int shotRand = rand() % (30 + pressure);
    int shot = p->getCloseShot(), freeThrows = 0;

    int foulRand = rand() % 6;

    if(foulRand == 0)
    {
        freeThrows = 2;
        fouls.addFoul(p->getTeam(), time);
    }

    if(shotRand < shot)
    {
       cout << "SCORE Close" << endl;
       updateScore(p->getTeam() - 1, 2);
       p->getStatList()->addTwoPoints();
       checkAssist();

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
        p->getStatList()->addMiss();

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

void Match::shootMedium(Player* p, int pressure)
{
    int shotRand = rand() % (35 + pressure);
    int shot = p->getMediumShot(), freeThrows = 0;

    int foulRand = rand() % 50;

    if(foulRand == 0)
    {
        freeThrows = 2;
        fouls.addFoul(p->getTeam(), time);
    }

    if(shotRand < shot)
    {
       cout << "SCORE Mid" << endl;
       updateScore(p->getTeam() - 1, 2);
       p->getStatList()->addTwoPoints();
       checkAssist();

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
        p->getStatList()->addMiss();

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

void Match::shootThree(Player *p, int pressure)
{
    int shotRand = rand() % (30 + pressure);
    int shot, freeThrows = 0;

    int foulRand = rand() % 100;

    if(foulRand == 0)
    {
        freeThrows = 3;
        fouls.addFoul(p->getTeam(), time);
    }
    if(p->getPosY() <= 0)
    {
        shot = (p->getThreeShot() / 4);
    }
    else
    {
        shot = p->getThreeShot();
    }

    if(shotRand < shot)
    {
       cout << "SCORE 3" << endl;

       updateScore(p->getTeam() - 1, 3);
       p->getStatList()->addThreePoints();

       checkAssist();
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
        p->getStatList()->addThreeMiss();

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

void Match::checkAssist()
{
    if(get<1>(assist) <= time + 3)
    {
        get<0>(assist)->getStatList()->addAssist();
    }
}

void Match::shootFreeThrow(Player *p, int numOfFreeThrows)
{
    teams[p->getTeam() - 1]->setUpFreeThrowOffence(p->getNumber());
    teams[getOtherTeam(p->getTeam())]->setUpFreeThrowDefence();

    int ft = p->getFreethrow();

    do
    {
        int ftProb = rand() % 22;
        if(ftProb < ft)
        {
            cout << "Free Throw: " << p->getNumber() << endl;
            p->getStatList()->addFreeThrowScore();

            updateScore(p->getTeam() - 1, 1);
            p->getStatList()->addPoint();

            if(numOfFreeThrows == 1)
            {
                setUpRestartInbound();
            }
        }
        else
        {
            cout << "Missed Free Throw: " << p->getNumber() << endl;
            p->getStatList()->addFreeThrow();

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
    int stealRand, stealRating, passRand, pass = p->getPass(), posX = teamMate->getPosX(), posY = teamMate->getPosY(), stolenNumber = 0;
    bool steal = false;
    Team team = *teams[getOtherTeam(p->getTeam())];
    Player *defender;
    vector<int> defenders = getDefendersForPass(getOtherTeam(p->getTeam()), p->getPosX(), p->getPosY(), posX, posY);
    if(defenders.size() > 0)
    {
        for(auto pos: defenders)
        {
            defender = team.getPlayer(pos);
            stealRating = defender->getSteal();
            stealRand = rand() % stealRating;
            passRand = rand() % (pass * 5);
            if(stealRand > passRand)
            {
                steal = true;
                stolenNumber = defender->getNumber();
            }
        }
    }


    if(steal)
    {
        cout << "Steal Pass: " << stolenNumber << endl;
        swapSides(stolenNumber);
    }
    else
    {
        cout << "Pass: " << teamMate->getNumber() << endl;
        assist = make_tuple(p, time);
        ball.setPlayerPosition(teams[teamMate->getTeam() - 1]->getPlayerPosition(teamMate->getNumber()));
        ball.setPos(teamMate->getPosX(), teamMate->getPosY());
    }
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
             ball.setPos(p->getPosX(), p->getPosY());

             if(ball.getTeam() == p->getTeam())
             {
                 cout << "Offensive Rebound: " << p->getNumber() << endl;
                 p->getStatList()->addOffensiveRebound();

                shotClock = 0;
             }
             else
             {
                 cout << "Defensive Rebound: " << p->getNumber() << endl;
                 p->getStatList()->addDefensiveRebound();

                 shotClock = 0;
                 swapSides(p->getNumber());
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
    ProbabilityVector probs(3);
    Team *team = teams[p->getTeam() - 1];
    int matchup, oppTeam = getOtherTeam(p->getTeam()), posValue, sag = 0, tight = 0, result;
    int defence = p->getDefence(), stealRating = p->getSteal(), defenceSetting;
    //get the defensive matchup of the player

    matchup = teams[p->getTeam() - 1]->getMatchup(*p);
    Player opposition = *teams[oppTeam]->getPlayer(matchup);


    //play tight if their matchup has the ball
    //play tight if their matchup is close to the basket
    //play loose if farther out
    if(p->getPosX() < 0)
    {
        p->movePlayer(5);
    }
    else if(ball.getPlayerPosition() == matchup)
    {
        posValue = opposition.getPosValue();
        defenceSetting = team->getDefenceSetting(matchup);

        if(defenceSetting == Team::TIGHT)
        {
            tight = 20 + posValue + defence;
            sag = (20 - defence)/2;
        }
        else
        {
            tight = (20 - defence)/2 + posValue;
            sag = 20 + defence;
        }

        probs.addProbability(tight);
        probs.addProbability(sag);

        if(opposition.getPosX() == p->getPosX() && opposition.getPosY() == p->getPosY())
        {
            probs.addProbability(stealRating);
        }

        result = probs.getRandomResult();
        if(result == 0)
        {
            moveDefenceTight(p, opposition);
        }
        else if(result == 1)
        {
            moveDefenceLoose(p, opposition);
        }
        else
        {
            steal(p, opposition);
        }

    }
    else
    {
        posValue = opposition.getPosValue();
        defenceSetting = team->getDefenceSetting(matchup);

        if(defenceSetting == Team::TIGHT)
        {
            tight = 20 + posValue + defence;
            sag = (20 - defence)/2;
        }
        else
        {
            tight = (20 - defence)/2 + posValue;
            sag = 20 + defence;
        }

        probs.addProbability(tight);
        probs.addProbability(sag);

        vector<Player *> otherPlayers = teams[oppTeam]->getOtherPlayers(matchup);

        for(auto &player: otherPlayers)
        {
            if(player->isDribbleDrive())
            {
                probs.addProbability(10 + defence);
                break;
            }
        }

        result = probs.getRandomResult();
        if(result == 0)
        {
            moveDefenceTight(p, opposition);
        }
        else if(result == 1)
        {
            moveDefenceLoose(p, opposition);
        }
        else if(result == 2)
        {
            moveTowardBasket(p);
        }
    }
}

void Match::moveDefenceLoose(Player *p, Player opposition)
{
    //get player and opposition positions
    int oppPosX = opposition.getPosX(), oppPosY = opposition.getPosY();

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

    moveDefender(p, oppPosX, oppPosY);
}

void Match::moveDefenceTight(Player* p, Player opposition)
{
    int oppPosX = opposition.getPosX(), oppPosY = opposition.getPosY();
    moveDefender(p, oppPosX, oppPosY);
}


void Match::moveTowardBasket(Player* p)
{
    int posX = p->getPosX(), basketX = 6, basketY, moveDirection;

    if(posX < 4)
    {
        basketY = 3;
    }
    else
    {
        basketY = 4;
    }

   moveDefender(p, basketX, basketY);
}

void Match::moveDefender(Player *p, int destPosX, int destPosY)
{
    int moveDirection = 4, posX = p->getPosX(), posY = p->getPosY();
    if(posY < destPosY)
    {
        if(posX < destPosX)
        {
            moveDirection = 8;
        }
        else if(posX > destPosX)
        {
            moveDirection = 6;
        }
        else
        {
            moveDirection = 7;
        }
    }
    else if(posY > destPosY)
    {
        if(posX < destPosX)
        {
            moveDirection = 2;
        }
        else if(posX > destPosX)
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
        if(posX < destPosX)
        {
            moveDirection = 5;
        }
        else if(posX > destPosX)
        {
            moveDirection = 3;
        }
        else
        {
            moveDirection = 4;
        }
    }

    if(moveDirection != 4)
    {
        for(int i = 1; i < 6; i++)
        {
            Player opp = *teams[getOtherTeam(p->getTeam())]->getPlayer(i);
            if(opp.getPosX() == posX && opp.getPosY() == posY)
            {
                int screenRand = rand() % 5;

                if(screenRand == 0)
                {
                    cout << "BUMP: " << p->getNumber() << " " << opp.getNumber() << endl;
                    moveDirection = 4;
                    break;
                }
            }
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

void Match::steal(Player *p, Player opposition)
{
    int stealRand = rand() % 400, steal = p->getSteal();

    if(stealRand < steal)
    {
        cout << "Steal: " << p->getNumber() << endl;
        swapSides(p->getNumber());
    }
    else if(stealRand <= 20)
    {
        cout << "Illegal contact: " << p->getNumber() << endl;
        fouls.addFoul(p->getTeam(), time);
        if(fouls.getTeamBonus(p->getTeam()) == true)
        {
            shootFreeThrow(p, 2);
        }
        else
        {
            setUpOffensiveInbound();
            if(shotClock < 14)
            {
                shotClock = 14;
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
