#include "Match.h"

int Match::simSpeed = 1000;

Match::Match(Team *teamOne, Team *teamTwo, MatchScreen *newScreen):manDefence(teamOne, teamTwo), zoneDefence(teamOne, teamTwo)
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
    screen = newScreen;

    teamOne->pickStartingTeam();
    teamTwo->pickStartingTeam();
    guiInit();
    setOrderOfPlay();
}

Match::~Match()
{

}

void Match::sim()
{
    for(quarter = 0; quarter < 4; quarter++)
    {
        if(quarter==0)
        {
            jumpBall();
        }
        else if(quarter == 2 || quarter == 1)
        {
           int team = getOtherTeam(firstPossession);
           ball.setTeam(team + 1);
           ball.setPlayerPosition(3);

           teamOne->restartInbound(team + 1);
           teamTwo->restartInbound(team + 1);
           gameState = INBOUND;
        }
        else
        {
            int team = firstPossession;
            ball.setTeam(team);
            ball.setPlayerPosition(3);

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
                if(screen != NULL)
                {
                    screen->updateTime(time, shotClock);
                }
                endOfPossession = false;
                cout << "Q" << quarter+1 << " TIME: " << time << " Shotclock: " << shotClock << endl;

                cout << "Ball: " << ball.getTeam() << " " << ball.getPlayerPosition() << endl;

                simPlayers();
            }
            if(!endOfPossession)
            {
                setUpRestartInbound();
            }
        }
    }

    while(score[0] == score[1])
    {
        for(time = 300; time > 0;)
        {
            cout << "Score: " << score[0] << "-" << score[1] << endl;
            for(shotClock = 24; shotClock >= 0 && time >= 0; shotClock--, time--)
            {
                if(time < 24 && shotClock == 24)
                {
                    shotClock = time;
                }
                if(screen != NULL)
                {
                    screen->updateTime(time, shotClock);
                }
                cout << "OT" << " TIME: " << time << " Shotclock: " << shotClock << endl;
                cout << "Ball: " << ball.getTeam() << " " << ball.getPlayerPosition() << endl;

                simPlayers();
            }
            if(!endOfPossession)
            {
                setUpRestartInbound();
            }
        }
    }
    guiUpdateCourt();
    cout << "Game Over" << endl;
    cout << "Score: " << score[0] << "-" << score[1] << endl;
    shotMap.printHeatMap();
    for(int i = 1; i <= teamOne->getRosterSize(); i++)
    {
        teamOne->getPlayer(i)->updateOverAllStats();
    }
    for(int i = 1; i <= teamTwo->getRosterSize(); i++)
    {
        teamTwo->getPlayer(i)->updateOverAllStats();
    }

    //analyser.writeToFile();
}

int* Match::getScore()
{
    return score;
}

Team* Match::getTeamOne()
{
    return teamOne;
}

Team* Match::getTeamTwo()
{
    return teamTwo;
}

void Match::simPlayers()
{
    setOrderOfPlay();

    endOfPossession = false;

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

        if(endOfPossession)
        {
            shotClock = 0;
            break;
        }
    }
    guiUpdateCourt();
    QTime dieTime= QTime::currentTime().addMSecs(Match::simSpeed);
        while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    if(time%60 == 0)
    {
        teamOne->updateEnergy();
        teamTwo->updateEnergy();
    }
    if(printing)
    {
        printCourt();
    }
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
    std::ofstream outfile;

    outfile.open("../stats/results.txt", std::ios_base::app);
    outfile << teamOne->getName() << "," << score[0] << "," << teamTwo->getName() << "," << score[1] << endl;

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

void Match::printValue(string valueName, int value)
{
    if(printing)
    {
        cout << valueName << ": " << value << endl;
    }
}

void Match::printValue(string valueName, int value, int valueTwo)
{
    if(printing)
    {
        cout << valueName << ": " << value << " " << valueTwo << endl;
    }
}

void Match::printValue(string valueName)
{
    if(printing)
    {
        cout << valueName << endl;
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
    endOfPossession = true;
}

void Match::setUpRestartInbound()
{
    endOfPossession = true;
    teams[0]->swapSides();
    teams[1]->swapSides();
    ball.changeTeam();
    ball.setPlayerPosition(3);

    int team = ball.getTeam();
    teamOne->restartInbound(team);
    teamTwo->restartInbound(team);
    gameState = INBOUND;
}

void Match::setUpOffensiveInbound()
{
    endOfPossession = true;
    teamOne->swapPlayers(time, quarter);
    teamTwo->swapPlayers(time, quarter);
    guiUpdatePlayers();
    ball.setPlayerPosition(4);

    int team = ball.getTeam();
    teamOne->offensiveInbound(team);
    teamTwo->offensiveInbound(team);
    gameState = INBOUND;
    setOrderOfPlay();
}

void Match::setUpOwnSideInbound()
{
    endOfPossession = true;
    teamOne->swapPlayers(time, quarter);
    teamTwo->swapPlayers(time, quarter);
    guiUpdatePlayers();

    ball.setPlayerPosition(4);

    int team = ball.getTeam();
    teamOne->ownSideInbound(team);
    teamTwo->ownSideInbound(team);
    gameState = INBOUND;
    setOrderOfPlay();
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

        //cout << "Jump Ball: Team 1" << endl;
        printValue("Jump Ball Team", 1);
        guiUpdateCommentary(16, playerOne);
    }
    else if(jumpWinner == 1)
    {
        //cout << "Jump Ball: Team 2" << endl;
        printValue("Jump Ball Team", 2);
        guiUpdateCommentary(16, playerTwo);

        teams[0]->swapSides();
        teams[1]->swapSides();
        ball.setTeam(2);
    }
    gameState = INPLAY ;
    guiUpdateCourt();

}
//================================



void Match::updateScore(int team, int points)
{
    score[team]+=points;
    if(screen != NULL)
    {
        screen->updateScore(score[0], score[1]);
    }
}

//================================
// GUI Functions
//================================

void Match::guiUpdatePlayers()
{
    if(screen != NULL)
    {
        screen->updatePlayers();
    }
}

void Match::guiUpdateCommentary(int type, Player *playerOne, Player *playerTwo)
{
    if(screen != NULL)
    {
        screen->updateCommentary(type, playerOne, playerTwo);
    }
}

void Match::guiUpdateStat()
{
    if(screen != NULL)
    {
        screen->updateStat();
    }
}

void Match::guiInit()
{
    if(screen != NULL)
    {
        screen->initMatchScreen(teamOne, teamTwo);
    }
}

void Match::guiUpdateCourt()
{
    if(screen != NULL)
    {
        screen->updateCourt(&ball);
    }
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
        vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());
        int xSpace = 0, ySpace = 0, spacingModifier = 0, moveModifier = 2;

        for(auto &player: otherPlayers)
        {
            xSpace += x - player->getPosX();
            ySpace += y - player->getPosY();
        }

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
                    spacingModifier = 0;
                    if(j < x && xSpace < 0)
                    {
                        spacingModifier += moveModifier;
                    }
                    else if(j > x && xSpace > 0)
                    {
                        spacingModifier += moveModifier;
                    }

                    if(i < y && ySpace < 0)
                    {
                        spacingModifier += moveModifier;
                    }
                    else if(i > y && ySpace > 0)
                    {
                        spacingModifier += moveModifier;
                    }
                    probs.addProbability(p->getPosValue(j, i) + spacingModifier);
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
        int playerStatModifier = calculateStatModifier(p);
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
            posValue = p->getPosValue() + ((shotClockFactor - shotClock)*2) - pressure + ((4 - p->getRange()) * 2) + playerStatModifier;
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
                int statModifier = calculateStatModifier(player);
                posValue = player->getPosValue() + (p->getPass() / 4) + statModifier - abs((x - player->getPosX()) + (y - player->getPosY()));
                if(defenders.size() > 0)
                {
                    posValue -= (defenders.size() * 2);
                }
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
        ProbabilityVector finalProbabilities = probs + *p->getStrategyVector();
        if(printing) finalProbabilities.printVector();

        int action  = finalProbabilities.getRandomResult();

        if(action < 9)
        {
            //cout << "Move: " << action << endl;
            printValue("Move", action);

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

        //analyser.addDecision(p->getNumber(), action);
    }
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
        ProbabilityVector probs(5);
        // Pass out of drive
        vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());

        for(auto &player: otherPlayers)
        {
            int posValue = 0;
            vector<int> defenders = getDefendersForPass(getOtherTeam(p->getTeam()), posX, posY, player->getPosX(), player->getPosY());
            if(player->getPosX() >= 0)
            {
                posValue = player->getPosValue() + (p->getPass() / 4) - abs((posX - player->getPosX()) + (posY - player->getPosY()));
            }

            if(defenders.size() > 0)
            {
                posValue -= (defenders.size() * 4);
            }
            probs.addProbability(posValue);
        }

        //drive

        probs.addProbability(100 - teams[getOtherTeam(p->getTeam())]->getPressure(posX, posY));

        if(printing) probs.printVector();

        int action  = probs.getRandomResult();

        if(action < 4)
        {
            //cout << "Pass from drive" << endl;
            printValue("Pass from drive", p->getNumber());
            p->setDribbleDrive(false);

            pass(p, otherPlayers[action]);
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
                Player *opp = teams[getOtherTeam(p->getTeam())]->getPlayer(i);
                if(opp->getPosX() == posX && opp->getPosY() == posY)
                {
                    int screenRand = rand() % 50;

                    if(screenRand < 25)
                    {
                        //cout << "Drive Stopped: " << p->getNumber() << " " << opp.getNumber() << endl;
                        printValue("Drive Stopped", p->getNumber(), opp->getNumber());
                        move = 4;
                        p->setDribbleDrive(false);
                        break;
                    }
                    else if(screenRand < 29)
                    {
                        //cout << "Blocking foul: " << opp.getNumber() << " on " << p->getNumber() << endl;
                        printValue("Blocking foul", opp->getNumber(), p->getNumber());

                        fouls.addFoul(p->getTeam(), time);
                        if(fouls.getTeamBonus(p->getTeam()) == true)
                        {
                            shootFreeThrow(p, 2);
                        }
                        else
                        {
                            setUpOffensiveInbound();
                            /*
                            if(shotClock < 14)
                            {
                                shotClock = 14;
                            }
                            */
                        }
                    }
                    else if(screenRand == 31)
                    {
                        //cout << "Offensive foul: " << p->getNumber() << endl;
                        printValue("Offensive Foul", p->getNumber());
                        ball.changeTeam();
                        shotClock = 0;
                        setUpOwnSideInbound();
                    }
                }
            }
            //cout << "Drive: " << move << endl;
            printValue("Drive", move);
            p->movePlayer(move);
        }

    }
}

//==============================

vector<int> Match::getDefendersForPass(int team, int x1, int y1, int x2, int y2)
{
    vector<int> defenders;
    vector<int> passCoordinates;
    Team *defendingTeam = teams[team];
    float slope;
    if((x2 - x1) == 0)
    {
        slope = 2;
    }
    else
    {
       slope = fabs(((float)y2 - (float)y1)/((float)x2 - (float)x1));
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
            passCoordinates.push_back(i);
            passCoordinates.push_back(j);
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
           passCoordinates.push_back(i);
           passCoordinates.push_back(j);
            diff -= dy;
            if(diff < 0)
            {
                j += step;
                diff += dx;
            }
        }
    }

    for(int i = 1; i < 6; i++)
    {
        Player *defender = defendingTeam->getPlayer(i);
        int passDotProduct = (x2 - x1) * (defender->getPosX() - x1) + (y2 - y1) * (defender->getPosY() - y1);

        if(passDotProduct > 0)
        {
            for(int c = 0; c < passCoordinates.size(); c+=2)
            {
                if(defender->getPosX() == passCoordinates[c] && defender->getPosY() == passCoordinates[c+1])
                {
                    defenders.push_back(i);
                    break;
                }
            }
        }
    }

    return defenders;
}

int Match::calculateStatModifier(Player *p)
{
    int modifier = 0;
    StatList *stats = p->getStatList();
    if(p->getRange() == 4)
    {
        modifier = (stats->getPoints() * stats->getThreeShootingPercentage());
    }
    else
    {
        modifier = (stats->getPoints() * stats->getShootingPercentage());
    }
    return modifier/2;
}

//================================
// Player Offense Actions Results
//================================

void Match::shoot(Player* p, int pressure)
{
    shotMap.incrementValue(p->getPosX(), p->getPosY());
    int range = p->getRange();
    //analyser.addShot(shotClock);
    if(range == 1)
    {
        shootTwo(p, pressure, p->getUnderBasketShot(), 30, 5, "Under Basket" );
    }
    else if(range == 2)
    {
        shootTwo(p, pressure, p->getCloseShot(), 32, 5, "Close" );
    }
    else if(range == 3)
    {
        shootTwo(p, pressure, p->getMediumShot(), 37, 50, "Mid Range" );
    }
    else
    {
        shootThree(p, pressure);
    }
}

void Match::shootTwo(Player *p, int pressure, int shot, int shootRand, int foulRand, string type)
{
    int catchAndShootMod = 0;
    if(get<1>(assist) <= time + 1)
    {
        catchAndShootMod = 2;
    }

    int shotRand = rand() % (shootRand + pressure - catchAndShootMod);
    int freeThrows = 0;

    int foul = rand() % foulRand;

    if(foul == 0)
    {
        freeThrows = 2;
        fouls.addFoul(p->getTeam(), time);
    }

    if(shotRand < shot)
    {
       updateScore(p->getTeam() - 1, 2);

       printValue("SCORE " + type);
       if(type == "Mid Range")
       {
           guiUpdateCommentary(2, p);
       }
       else if(type == "Close")
       {
           guiUpdateCommentary(3, p);
       }
       else
       {
           guiUpdateCommentary(4, p);
       }

       p->getStatList()->addTwoPoints();
       guiUpdateStat();
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
        //cout << "MISS " << type << endl;
        printValue("Miss" + type);
        guiUpdateCommentary(12, p);

        p->getStatList()->addMiss();
        guiUpdateStat();

        if(freeThrows == 0)
        {
            if(block(p))
            {
                blockedShot(p->getPosX(), p->getPosY());
            }
            else
            {
                rebound();
            }
        }
    }

    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}

void Match::shootThree(Player *p, int pressure)
{
    int catchAndShootMod = 0;
    if(get<1>(assist) <= time + 1)
    {
        catchAndShootMod = 2;
    }

    int shotRand = rand() % (29 + pressure - catchAndShootMod);
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
        printValue("Score 3");
        guiUpdateCommentary(1, p);
        updateScore(p->getTeam() - 1, 3);

       p->getStatList()->addThreePoints();
       guiUpdateStat();

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
        printValue("Miss 3");
        p->getStatList()->addThreeMiss();
        guiUpdateStat();

        if(freeThrows == 0)
        {
            if(block(p))
            {
                blockedShot(p->getPosX(), p->getPosY());
            }
            else
            {
                rebound();
            }
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
        guiUpdateStat();
    }
}

void Match::shootFreeThrow(Player *p, int numOfFreeThrows)
{
    teamOne->swapPlayers(teams[p->getTeam() - 1]->getPlayerPosition(p->getNumber()), time, quarter);
    teamTwo->swapPlayers(teams[p->getTeam() - 1]->getPlayerPosition(p->getNumber()), time, quarter);
    guiUpdatePlayers();

    teams[p->getTeam() - 1]->setUpFreeThrowOffence(p->getNumber());
    teams[getOtherTeam(p->getTeam())]->setUpFreeThrowDefence();

    int ft = p->getFreethrow();
    do
    {
        int ftProb = rand() % 20;
        if(ftProb <= ft)
        {
            //cout << "Free Throw: " << p->getNumber() << endl;
            printValue("Free Throw", p->getNumber());
            p->getStatList()->addFreeThrowScore();
            guiUpdateStat();

            updateScore(p->getTeam() - 1, 1);

            if(numOfFreeThrows == 1)
            {
                setUpRestartInbound();
            }
        }
        else
        {
            //cout << "Missed Free Throw: " << p->getNumber() << endl;
            printValue("Missed Free Throw", p->getNumber());
            p->getStatList()->addFreeThrow();
            guiUpdateStat();

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
    Team *team = teams[getOtherTeam(p->getTeam())];
    Player *defender;
    vector<int> defenders = getDefendersForPass(getOtherTeam(p->getTeam()), p->getPosX(), p->getPosY(), posX, posY);
    if(defenders.size() > 0)
    {
        for(auto pos: defenders)
        {
            defender = team->getPlayer(pos);
            stealRating = defender->getSteal();
            stealRand = rand() % stealRating;
            passRand = rand() % (pass * 25);
            if(stealRand > passRand)
            {
                steal = true;
                stolenNumber = defender->getNumber();
                defender->getStatList()->addSteal();
                guiUpdateStat();

            }
        }
    }


    if(steal)
    {
        //cout << "Steal Pass: " << stolenNumber << endl;
        printValue("Steal Pass", stolenNumber);
        swapSides(stolenNumber);
    }
    else
    {
        //cout << "Pass: " << teamMate->getNumber() << endl;
        printValue("Pass", teamMate->getNumber());
        guiUpdateCommentary(15, p, teamMate);
        assist = make_tuple(p, time);
        ball.setPlayerPosition(teams[teamMate->getTeam() - 1]->getPlayerPosition(teamMate->getNumber()));
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
            int range = player->getRange();
            if(range <= reboundRange)
            {
                if(player->getTeam() == ball.getTeam())
                {
                    probs.addProbability(player->getOffRebound());
                }
                else
                {
                    probs.addProbability(player->getDefRebound() * 3);
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
                 //cout << "Offensive Rebound: " << p->getNumber() << endl;
                 printValue("Offensive Rebound", p->getNumber());
                 guiUpdateCommentary(8, p);
                 p->getStatList()->addOffensiveRebound();
                 guiUpdateStat();

                 endOfPossession = true;
             }
             else
             {
                 //cout << "Defensive Rebound: " << p->getNumber() << endl;
                 printValue("Defensive Rebound", p->getNumber());
                 guiUpdateCommentary(9, p);
                 p->getStatList()->addDefensiveRebound();
                 guiUpdateStat();

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
    Team *team = teams[p->getTeam() - 1];

    if(p->getPosX() < 0)
    {
        p->movePlayer(5);
    }
    else if(team->getDefence() == Team::ZONE)
    {
        vector<int> result = zoneDefence.moveZoneDefence(p, &ball);
        if(result[0] == -1)
        {
            steal(p);
        }
        else
        {
            moveDefender(p, result[0], result[1]);
        }
    }
    else
    {
        vector<int> result = manDefence.moveManDefence(p, &ball);
        if(result[0] == -1)
        {
            steal(p);
        }
        else
        {
            moveDefender(p, result[0], result[1]);
        }
    }
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
            Player *opp = teams[getOtherTeam(p->getTeam())]->getPlayer(i);
            if(opp->getPosX() == posX && opp->getPosY() == posY)
            {
                int screenRand = rand() % 5;

                if(screenRand == 0)
                {
                    //cout << "BUMP: " << p->getNumber() << " " << opp->getNumber() << endl;
                    printValue("Bump", p->getNumber(), opp->getNumber());
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

bool Match::block(Player *p)
{
    for(int i = 1; i < 6; i++)
    {
        Player *opp = teams[getOtherTeam(p->getTeam())]->getPlayer(i);
        if(opp->getPosX() == p->getPosX() && opp->getPosY() == p->getPosY())
        {
            int block = rand() % 175;

            if(block < (opp->getBlock() * (opp->getBlock() / 4)))
            {
                //cout << "Block: " << opp->getNumber() << endl;
                printValue("Block", opp->getNumber());
                guiUpdateCommentary(14,opp, p);
                opp->getStatList()->addBlock();
                guiUpdateStat();

                return true;
            }
        }
    }
    return false;
}

void Match::blockedShot(int posX, int posY)
{
    int randX = (rand() % 3) + (posX - 1), randY = (rand() % 3) + (posY - 1);

    if(randY < 0 || randY > 7 || randX > 6)
    {
        setUpOffensiveInbound();
    }
    else
    {
        vector<Player *> players;
        ProbabilityVector probs(10);
        int count = 0, startX = randX, endX = randX, startY = randY, endY = randY;
        do
        {
            for(auto &player: orderOfPlay)
            {
                for(int i = startX; i <= endX; i++)
                {
                    for(int j = startY; j <= endY; j++)
                    {
                        if(player->getPosX() == i && player->getPosY() == j)
                        {
                            probs.addProbability(player->getDefRebound());
                            players.push_back(player);
                            count++;
                        }
                    }
                }

            }
            startX-=1;
            endX+=1;
            startY-=1;
            endY+=1;
        }while(count == 0);

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
         if(ball.getTeam() != p->getTeam())
         {
             shotClock = 0;
             swapSides(p->getNumber());
         }
    }
}

void Match::steal(Player *p)
{
    int stealRand = rand() % 400, steal = p->getSteal();

    if(stealRand < steal)
    {
        //cout << "Steal: " << p->getNumber() << endl;
        printValue("Steal", p->getNumber());
        p->getStatList()->addSteal();
        guiUpdateStat();

        swapSides(p->getNumber());
    }
    else if(stealRand <= 25)
    {
        //cout << "Illegal contact: " << p->getNumber() << endl;
        printValue("Illegal Contact", p->getNumber());
        fouls.addFoul(p->getTeam(), time);
        if(fouls.getTeamBonus(p->getTeam()) == true)
        {
            shootFreeThrow(p, 2);
        }
        else
        {
            setUpOffensiveInbound();
            /*
            if(shotClock < 14)
            {
                shotClock = 14;
            }
            */
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

/*
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
       score[p->getTeam() - 1]+=2;
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
            if(block(p))
            {
                blockedShot(p->getPosX(), p->getPosY());
            }
            else
            {
                rebound();
            }
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
       score[p->getTeam() - 1]+=2;
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
            if(block(p))
            {
                blockedShot(p->getPosX(), p->getPosY());
            }
            else
            {
                rebound();
            }
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
       score[p->getTeam() - 1]+=2;
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
            if(block(p))
            {
                blockedShot(p->getPosX(), p->getPosY());
            }
            else
            {
                rebound();
            }
        }
    }
    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}
*/
