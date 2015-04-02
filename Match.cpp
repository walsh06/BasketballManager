#include "Match.h"

int Match::simSpeed = 1000;

/** Match Constructor */
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

/** Match Destructor */
Match::~Match()
{

}

/** Method to start simulating a match */
void Match::sim()
{
    //loop through all quarters
    for(quarter = 0; quarter < 4; quarter++)
    {
        //check which quarter the match is in
        //perform appropriate start
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
        //reset fouls for the quarter
        fouls.resetFouls();
        //countdown the time for a quarter
        for(time = 720; time > 0;)
        {
            cout << "Score: " << score[0] << "-" << score[1] << endl;
            //countdown the shotclock for a possession
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

    //check if the scores are tied at the end
    //play overtime if they are
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
    //shotMap.printHeatMap();
    //update stats
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

/** Return game score */
int* Match::getScore()
{
    return score;
}

/** Return team one */
Team* Match::getTeamOne()
{
    return teamOne;
}

/** Return team two */
Team* Match::getTeamTwo()
{
    return teamTwo;
}

/** Called every second to simulate players in the game */
void Match::simPlayers()
{
    //set the order players simulate
    setOrderOfPlay();

    endOfPossession = false;

    for(auto &player : orderOfPlay)
    {
        //if players team has the ball
        if(player->getTeam() == ball.getTeam())
        {
            //if the player has the ball
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
            //team does not have the ball
            moveDefence(player);
        }

        if(endOfPossession)
        {
            shotClock = 0;
            break;
        }
    }
    //update the gui
    guiUpdateCourt();
    QTime dieTime= QTime::currentTime().addMSecs(Match::simSpeed);
        while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    //update energy every minute
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

/** Set the sim speed of the match */
void Match::setSimSpeed(int speed)
{
    Match::simSpeed = speed;
}

/** Set the order of players each turn */
void Match::setOrderOfPlay()
{
    //clear the order from last time
    orderOfPlay.clear();
    vector<Player *> players;
    map<int, Player*> playersWithSpeed;
    int speedOne, speedTwo;
    //loop through players on the court
    for(int j =1; j < 6; j++)
    {
        Player *p1 = teamOne->getPlayer(j);
        Player *p2 = teamTwo->getPlayer(j);
        //use a players speed and random number to get their preference
        //higher preferences go first
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
    //push players into vector in order
    std::vector<Player*>::iterator it = orderOfPlay.begin();
    for(auto &player: playersWithSpeed)
    {
        orderOfPlay.push_back(player.second);
    }
}

/** Get the opposite number team */
int Match::getOtherTeam(int team)
{
    if(team == 1) return 1;
    else return 0;
}

/** Get score difference for the team */
int Match::getScoreDifference(int team)
{
    return score[getOtherTeam(team)] - score[team];
}

/** Write match stats to file */
void Match::writeMatchStats(string filename)
{
    std::ofstream outfile;
    //open file
    outfile.open("../stats/results.txt", std::ios_base::app);
    outfile << teamOne->getName() << "," << score[0] << "," << teamTwo->getName() << "," << score[1] << endl;

    vector<Player *> rosterOne = teamOne->getRoster(), rosterTwo = teamTwo->getRoster();
    //loop through team one and team two and write each players stats
    for(int i = 0; i < 10; i++)
    {
        Player *player = rosterOne[i];
        //cout << "Player: " << player->getNumber() << " Team: " << player->getTeam() << endl;
        //player->getStatList()->printShootingStats();
        //player->getStatList()->printReboundingStats();
        //cout << endl;
        player->getStatList()->writeToFile(filename, i + 1);
    }

    for(int i = 0; i < 10; i++)
    {
        Player *player = rosterTwo[i];
        //cout << "Player: " << player->getNumber() << " Team: " << player->getTeam() << endl;
        //player->getStatList()->printShootingStats();
        //player->getStatList()->printReboundingStats();
        //cout << endl;
        player->getStatList()->writeToFile(filename,i + 1);
    }
}

/** Print a single value */
void Match::printValue(string valueName, int value)
{
    if(printing)
    {
        cout << valueName << ": " << value << endl;
    }
}

/** Print two values */
void Match::printValue(string valueName, int value, int valueTwo)
{
    if(printing)
    {
        cout << valueName << ": " << value << " " << valueTwo << endl;
    }
}

/** Print value name only */
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
/** Swapsides of both teams */
void Match::swapSides(int playerNum)
{
    //change sides
    teams[0]->swapSides();
    teams[1]->swapSides();
    //set ball control
    ball.changeTeam();
    ball.setPlayerPosition(teams[ball.getTeam() - 1]->getPlayerPosition(playerNum));
    endOfPossession = true;
}

/** Set up both teams after a score */
void Match::setUpRestartInbound()
{
    endOfPossession = true;
    teams[0]->swapSides();
    teams[1]->swapSides();
    ball.changeTeam();
    ball.setPlayerPosition(3);

    int team = ball.getTeam();
    //set up teams for inbound
    teamOne->restartInbound(team);
    teamTwo->restartInbound(team);
    gameState = INBOUND;
}

/** Set up both teams for an offensive inbound */
void Match::setUpOffensiveInbound()
{
    endOfPossession = true;
    //make subs if possible
    teamOne->swapPlayers(time, quarter);
    teamTwo->swapPlayers(time, quarter);
    guiUpdatePlayers();
    ball.setPlayerPosition(4);

    int team = ball.getTeam();
    //set up teams for offensive inbound
    teamOne->offensiveInbound(team);
    teamTwo->offensiveInbound(team);
    gameState = INBOUND;
    setOrderOfPlay();
}

/** Set up both teams for an inbound */
void Match::setUpOwnSideInbound()
{
    endOfPossession = true;
    //make subs if possible
    teamOne->swapPlayers(time, quarter);
    teamTwo->swapPlayers(time, quarter);
    guiUpdatePlayers();

    ball.setPlayerPosition(4);

    int team = ball.getTeam();
    //set up teams for inbound
    teamOne->ownSideInbound(team);
    teamTwo->ownSideInbound(team);
    gameState = INBOUND;
    setOrderOfPlay();
}

/** Simulate a jump ball */
void Match::jumpBall()
{
    //get the centres
    Player* playerOne = teamOne->getPlayer(5), *playerTwo = teamTwo->getPlayer(5);
    //set up the start of the games
    teamOne->setUpStartGame(); teamTwo->setUpStartGame();
    printCourt();

    ProbabilityVector jumpVector(2);
    //get rebound skills of both players
    jumpVector.addProbability(playerOne->getDefRebound());
    jumpVector.addProbability(playerTwo->getDefRebound());

    //get the winner
    int jumpWinner = jumpVector.getRandomResult();

    //give the point guard possession
    ball.setPlayerPosition(1);

    firstPossession = jumpWinner + 1;

    //set the teams for regular play
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


/** Update the match score */
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

/** Update the players on the match screen */
void Match::guiUpdatePlayers()
{
    if(screen != NULL)
    {
        screen->updatePlayers();
    }
}

/** Update the commentary on the match screen for event type*/
void Match::guiUpdateCommentary(int type, Player *playerOne, Player *playerTwo)
{
    if(screen != NULL)
    {
        screen->updateCommentary(type, playerOne, playerTwo);
    }
}

/** Update the stats in the match screen */
void Match::guiUpdateStat()
{
    if(screen != NULL)
    {
        screen->updateStat();
    }
}

/** Setup the match screen */
void Match::guiInit()
{
    if(screen != NULL)
    {
        screen->initMatchScreen(teamOne, teamTwo);
    }
}

/** Update the court view of the match screen */
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

/** Move an offensive player without the ball */
void Match::move(Player* p)
{
    if(p->getPosX() < 0)
    {
        //move right if on their own side of the court
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
            //calculate the spacing between teammates for x and y directions
            xSpace += x - player->getPosX();
            ySpace += y - player->getPosY();
        }

        for(int i = y - 1; i <= y + 1; i++)
        {
            for(int j = x - 1; j <= x + 1; j++)
            {
                //if outside the court add a 0 weight
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
                    //calculate the spacingmodifier for a player
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

                    //calculate the weight for a given direction
                    probs.addProbability(p->getPosValue(j, i) + spacingModifier);
                }
            }
        }
        //move a player in the direction from the vector
        p->movePlayer(probs.getRandomResult());
    }
}

/** Used for an offensive player to make decision with the ball */
void Match::withBall(Player* p, int shotClock)
{
    if(shotClock == 0)
    {
        //if shotclock is running out, take a shot
        shoot(p, teams[getOtherTeam(p->getTeam())]->getPressure(p->getPosX(), p->getPosY()));
    }
    else if(p->getPosX() < 0)
    {
        //move right if in their own side of the court
        p->movePlayer(5);
    }
    else if(p->isDribbleDrive())
    {
        //if driving to the basket continue to do so
        driveBasket(p);
    }
    else
    {
        //else make a decision

        int x = p->getPosX(), y = p->getPosY(), shotClockFactor = 12;
        int playerStatModifier = calculateStatModifier(p);
        //move 0-8, shoot 9, pass 10-13, drive 14
        ProbabilityVector probs(15);
        //=================
        //MOVEMENT
        //=================
        //get position values to calculate move weight
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
        //calculate weight for shooting decision
        int pressure = teams[getOtherTeam(p->getTeam())]->getPressure(p->getPosX(), p->getPosY());
        int defendersUnderBasket = teams[getOtherTeam(p->getTeam())]->getPlayersUnderBasket();
        int scoreDifference = getScoreDifference(p->getTeam());
        int posValue = (scoreDifference/4);

        if(p->getRange() == 1 && defendersUnderBasket == 0)
        {
            //raise weight if under basket with no defenders
            posValue = p->getPosValue() + 100;
        }
        else if(pressure == 0)
        {
            //raise weight if no pressure on shot
            posValue = p->getPosValue() + (shotClockFactor - shotClock) + 100;
        }
        else
        {
            //calculate the regular weight of a shot
            posValue = p->getPosValue() + ((shotClockFactor - shotClock)*2) - pressure + ((4 - p->getRange()) * 2) + playerStatModifier;
        }

        //add the weight for the vector
        probs.addProbability(posValue);


        //=================
        //PASSING
        //=================
        //calculate passing weights
        //get teammates
        vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());

        //loop through all teammates and calculate weight for each pass
        for(auto &player: otherPlayers)
        {
            int posValue = 0;
            //get the defenders in the way of a pass
            vector<int> defenders = getDefendersForPass(getOtherTeam(p->getTeam()), x, y, player->getPosX(), player->getPosY());
            if(player->getPosX() >= 0)
            {
                //evaluate stats of a player
                int statModifier = calculateStatModifier(player);
                //calculate weight
                posValue = player->getPosValue() + (p->getPass() / 4) + statModifier - abs((x - player->getPosX()) + (y - player->getPosY()));
                if(defenders.size() > 0)
                {
                    //lower weight for each defender in the way
                    posValue -= (defenders.size() * 2);
                }
            }
            probs.addProbability(posValue);
        }

        //=================
        //Drive Basket
        //=================
        //calculate drive basket weight
        int value = p->getUnderBasketShot(), underBasket = teams[getOtherTeam(p->getTeam())]->getPlayersUnderBasket();

        //if no players defending by the basket, increase the weight
        if(underBasket == 0)
        {
            value += 10;
        }

        probs.addProbability(value);
        //=================

        //add players strategy vector to the weights
        ProbabilityVector finalProbabilities = probs + *p->getStrategyVector();
        if(printing) finalProbabilities.printVector();

        //get a random action using weight
        int action  = finalProbabilities.getRandomResult();

        //perform resulting action
        if(action < 9)
        {
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

/** Function to perform an inbound pass */
void Match::passInbound(Player *p)
{
    ProbabilityVector probs(14);

    //get teammates
    vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());
    bool ownSide = p->getPosX() < 0;
    int x = p->getPosX(), y = p->getPosY(), team = getOtherTeam(p->getTeam());

    //loop through teammates
    for(auto &player: otherPlayers)
    {
        int posValue = 0;

        //if inbounding on ownside
        if(ownSide)
        {
            //and player is on the own side, add a weight
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
            //inbounding on opposition side
            //get defenders in the way of each teammate
            vector<int> defenders = getDefendersForPass(team, x, y, player->getPosX(), player->getPosY());

            //use previous passing decision algorithm
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

    //get the result and make the pass
    int action  = probs.getRandomResult();
    pass(p, otherPlayers[action]);
    gameState = INPLAY;
}

/** Function used to drive the basket */
void Match::driveBasket(Player *p)
{
    int posX = p->getPosX(), posY = p->getPosY();
    if(p->getRange() == 1)
    {
        //if they are under the basket, take the shot
        shoot(p, teams[getOtherTeam(p->getTeam())]->getPressure(posX, posY));
    }
    else
    {
        ProbabilityVector probs(5);
        // Calculate the pass out of drive

        // get teammates
        vector<Player*> otherPlayers = teams[p->getTeam() - 1]->getOtherPlayers(p->getNumber());

        for(auto &player: otherPlayers)
        {
            //use previous passing algorithm
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

        //continue drive

        //high weight of continued drive
        probs.addProbability(100 - teams[getOtherTeam(p->getTeam())]->getPressure(posX, posY));

        if(printing) probs.printVector();

        //get the result
        int action  = probs.getRandomResult();

        //perform the action
        if(action < 4)
        {
            printValue("Pass from drive", p->getNumber());
            p->setDribbleDrive(false);

            pass(p, otherPlayers[action]);
        }
        else
        {
            //calculate the direction needed to continue the drive
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

            //loop through all defenders
            for(int i = 1; i < 6; i++)
            {
                Player *opp = teams[getOtherTeam(p->getTeam())]->getPlayer(i);

                //if the defender shares the same square calculate result
                if(opp->getPosX() == posX && opp->getPosY() == posY)
                {
                    int screenRand = rand() % 50;

                    if(screenRand < 25)
                    {
                        //stop the players drive
                        printValue("Drive Stopped", p->getNumber(), opp->getNumber());
                        move = 4;
                        p->setDribbleDrive(false);
                        break;
                    }
                    else if(screenRand < 29)
                    {
                        //defensive foul
                        printValue("Blocking foul", opp->getNumber(), p->getNumber());

                        fouls.addFoul(p->getTeam(), time);
                        if(fouls.getTeamBonus(p->getTeam()) == true)
                        {
                            shootFreeThrow(p, 2);
                        }
                        else
                        {
                            setUpOffensiveInbound();
                        }
                    }
                    else if(screenRand == 31)
                    {
                        //offensive foul
                        printValue("Offensive Foul", p->getNumber());
                        ball.changeTeam();
                        shotClock = 0;
                        setUpOwnSideInbound();
                    }
                }
            }
            printValue("Drive", move);
            p->movePlayer(move);
        }

    }
}

//==============================

/** Return defenders in the path of a pass */
vector<int> Match::getDefendersForPass(int team, int x1, int y1, int x2, int y2)
{
    //create vectors for storing results
    vector<int> defenders;
    vector<int> passCoordinates;
    Team *defendingTeam = teams[team];

    //use bresenhams algorithm to calculate path of ball
    float slope;

    //get the slope of the path
    if((x2 - x1) == 0)
    {
        slope = 2;
    }
    else
    {
       slope = fabs(((float)y2 - (float)y1)/((float)x2 - (float)x1));
    }

    //if the slope is 1/45 degrees just iterate x and y
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
        //swap the x and y if the slope is greater than 1
        if(slope > 1)
        {
            swap(x1, y1);
            swap(x2, y2);
        }

        //swap the direction if the slop is going down
        if(x1 > x2)
        {
            swap(x1, x2);
            swap(y1, y2);
        }

        //calculate starting values, error and step
        int dx = x2 - x1, dy = y2 - y1, j = y1;
        float diff = dx / 2.0f;
        int step = (y1 < y2) ? 1 : -1;

        //loop through each x coordinate
        for(int i = x1; i <= x2; i++)
        {
           //store the x and y coordinates in vector
           passCoordinates.push_back(i);
           passCoordinates.push_back(j);
           //adjust the error
            diff -= dy;
            //if error is too big
            if(diff < 0)
            {
                //update the y
                j += step;
                diff += dx;
            }
        }
    }

    //loop through all defenders
    for(int i = 1; i < 6; i++)
    {
        Player *defender = defendingTeam->getPlayer(i);
        //calcualte dot product between passer->receiver and passer->defender
        int passDotProduct = (x2 - x1) * (defender->getPosX() - x1) + (y2 - y1) * (defender->getPosY() - y1);

        //if result is < 0 the defender is behind the passer and away from the path
        if(passDotProduct > 0)
        {
            //loop through all coordinates of the ball path
            for(int c = 0; c < passCoordinates.size(); c+=2)
            {
                //check if the defender is in a coordinate
                if(defender->getPosX() == passCoordinates[c] && defender->getPosY() == passCoordinates[c+1])
                {
                    defenders.push_back(i);
                    break;
                }
            }
        }
    }

    //return all players who are in path of the ball
    return defenders;
}

/** Calculate the stat modifier of a player */
int Match::calculateStatModifier(Player *p)
{
    int modifier = 0;
    StatList *stats = p->getStatList();
    //use three point if they are at range 4
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
/** Function to calculate the outcome of a shot */
void Match::shoot(Player* p, int pressure)
{
    shotMap.incrementValue(p->getPosX(), p->getPosY());
    int range = p->getRange();
    //analyser.addShot(shotClock);

    //choose appropriate function and variables for shot range
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

/** Function for taking a two point shot */
void Match::shootTwo(Player *p, int pressure, int shot, int shootRand, int foulRand, string type)
{
    int catchAndShootMod = 0;
    //increase shot chance if the shot is a "catch and shoot"
    if(get<1>(assist) <= time + 1)
    {
        catchAndShootMod = 2;
    }

    //calculate chance of scoring
    int shotRand = rand() % (shootRand + pressure - catchAndShootMod);
    int freeThrows = 0;

    //calculate chance of a foul occurring
    int foul = rand() % foulRand;

    //if foul occurred update fouls and add free throws
    if(foul == 0)
    {
        freeThrows = 2;
        fouls.addFoul(p->getTeam(), time);
    }

    //check if shot was succesful
    if(shotRand < shot)
    {
       //succesful shot
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

       //update stats
       p->getStatList()->addTwoPoints();
       guiUpdateStat();

       //check if assist occurred on the score
       checkAssist();

       //adjust free throws
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
        printValue("Miss" + type);
        guiUpdateCommentary(12, p);

        p->getStatList()->addMiss();
        guiUpdateStat();

        //check if the miss was a block or a rebound
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

    //shoot free throws if a foul occurred
    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}

/** Function for taking a three point shot */
void Match::shootThree(Player *p, int pressure)
{
    int catchAndShootMod = 0;
    //increase shot chance if the shot is a "catch and shoot"
    if(get<1>(assist) <= time + 1)
    {
        catchAndShootMod = 2;
    }

    //calculate chance of scoring
    int shotRand = rand() % (29 + pressure - catchAndShootMod);
    int shot, freeThrows = 0;

    //calculate chance of a foul occurring
    int foulRand = rand() % 100;

    //if foul occurred update fouls and add free throws
    if(foulRand == 0)
    {
        freeThrows = 3;
        fouls.addFoul(p->getTeam(), time);
    }

    //lower shot chance if away from three point line
    if(p->getPosY() <= 0)
    {
        shot = (p->getThreeShot() / 4);
    }
    else
    {
        shot = p->getThreeShot();
    }

    //check shot success
    if(shotRand < shot)
    {
        printValue("Score 3");
        guiUpdateCommentary(1, p);
        updateScore(p->getTeam() - 1, 3);

       p->getStatList()->addThreePoints();
       guiUpdateStat();

       checkAssist();

       //update free throws
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

        //check result of the miss
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
    //take free throws
    if(freeThrows > 0)
    {
        shootFreeThrow(p, freeThrows);
    }
}

/** Checks if assist occurred on a shot */
void Match::checkAssist()
{
    //if score happened in the last 3 seconds
    if(get<1>(assist) <= time + 3)
    {
        get<0>(assist)->getStatList()->addAssist();
        guiUpdateStat();
    }
}

/** Shoot free throws */
void Match::shootFreeThrow(Player *p, int numOfFreeThrows)
{
    //make subs before the free throws
    teamOne->swapPlayers(teams[p->getTeam() - 1]->getPlayerPosition(p->getNumber()), time, quarter);
    teamTwo->swapPlayers(teams[p->getTeam() - 1]->getPlayerPosition(p->getNumber()), time, quarter);
    guiUpdatePlayers();

    //set up the players for the free throw
    teams[p->getTeam() - 1]->setUpFreeThrowOffence(p->getNumber());
    teams[getOtherTeam(p->getTeam())]->setUpFreeThrowDefence();

    int ft = p->getFreethrow();

    //loop while the free throws are left
    do
    {
        //calculate free throw success
        int ftProb = rand() % 21;
        if(ftProb <= ft)
        {
            //free throw was succesful
            printValue("Free Throw", p->getNumber());
            p->getStatList()->addFreeThrowScore();
            guiUpdateStat();

            updateScore(p->getTeam() - 1, 1);

            //if the last free throw set up for inbound
            if(numOfFreeThrows == 1)
            {
                setUpRestartInbound();
            }
        }
        else
        {
            //free throw was missedd
            printValue("Missed Free Throw", p->getNumber());
            p->getStatList()->addFreeThrow();
            guiUpdateStat();

            //if its the last free throw simulate the rebound
            if(numOfFreeThrows == 1)
            {
                rebound();
            }
        }
        numOfFreeThrows--;
    }while(numOfFreeThrows > 0);

}

/** Function to simulate a pass between two players */
void Match::pass(Player* p, Player* teamMate)
{
    int stealRand, stealRating, passRand, pass = p->getPass(), posX = teamMate->getPosX(), posY = teamMate->getPosY(), stolenNumber = 0;
    bool steal = false;
    Team *team = teams[getOtherTeam(p->getTeam())];
    Player *defender;

    //get the defenders in the way of the pass
    vector<int> defenders = getDefendersForPass(getOtherTeam(p->getTeam()), p->getPosX(), p->getPosY(), posX, posY);

    //if there are defenders in the way
    if(defenders.size() > 0)
    {
        for(auto pos: defenders)
        {
            defender = team->getPlayer(pos);
            stealRating = defender->getSteal();
            //calculate the pass and steal probabilities
            stealRand = rand() % stealRating;
            passRand = rand() % (pass * 25);
            if(stealRand > passRand)
            {
                //if steal happens
                steal = true;
                stolenNumber = defender->getNumber();
                defender->getStatList()->addSteal();
                guiUpdateStat();

            }
        }
    }

    //steal happens or complete the pass
    if(steal)
    {
        printValue("Steal Pass", stolenNumber);
        swapSides(stolenNumber);
    }
    else
    {
        printValue("Pass", teamMate->getNumber());
        guiUpdateCommentary(15, p, teamMate);
        //update the assist tracker with last pass
        assist = make_tuple(p, time);
        ball.setPlayerPosition(teams[teamMate->getTeam() - 1]->getPlayerPosition(teamMate->getNumber()));
    }
}

/** Function to simulate a rebound */
void Match::rebound()
{
    ProbabilityVector probs(10);
    vector<Player *> players;
    int count = 0, reboundRange = 2;

    do{
        //loop through all players on the court
        for(auto &player: orderOfPlay)
        {
            int range = player->getRange();
            //if the player is in range of the rebound
            if(range <= reboundRange)
            {
                //add rebound ability as weight, defense weight increased
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

        //if players were in range
        if(count > 0)
        {
            Player *p;
            int pos;
            //if one player in range they get the bal
            if( count == 1)
            {
                p = players[0];
            }
            else
            {
                //if multiple players in range get the winner
                int result = probs.getRandomResult();
                p = players[result];
            }

            //get the winner
            pos = teams[p->getTeam() - 1]->getPlayerPosition(p->getNumber());

             ball.setPlayerPosition(pos);

             //check if the rebound was offensive or defensive
             if(ball.getTeam() == p->getTeam())
             {
                 printValue("Offensive Rebound", p->getNumber());
                 guiUpdateCommentary(8, p);
                 p->getStatList()->addOffensiveRebound();
                 guiUpdateStat();

                 endOfPossession = true;
             }
             else
             {
                 printValue("Defensive Rebound", p->getNumber());
                 guiUpdateCommentary(9, p);
                 p->getStatList()->addDefensiveRebound();
                 guiUpdateStat();

                 swapSides(p->getNumber());
             }
        }
        else
        {
            //update the range if no player found
            reboundRange++;
        }
    }while(count == 0);
}

//==============================

//================================
// Player Defense Actions
//================================

/** Simulate defender movement */
void Match::moveDefence(Player *p)
{
    Team *team = teams[p->getTeam() - 1];

    if(p->getPosX() < 0)
    {
        //move right if on the opposite side of the court
        p->movePlayer(5);
    }
    else if(team->getDefence() == Team::ZONE)
    {
        //if team is in zone defence

        //get the desired position of a zone defender
        vector<int> result = zoneDefence.moveZoneDefence(p, &ball);
        if(result[0] == -1)
        {
            //attempt steal
            steal(p);
        }
        else
        {
            //else move the defender to desired position
            moveDefender(p, result[0], result[1]);
        }
    }
    else
    {
        //if team in man defence

        //get the desired position of a zone defender
        vector<int> result = manDefence.moveManDefence(p, &ball);
        if(result[0] == -1)
        {
            //attempt steal
            steal(p);
        }
        else
        {
            //else move the defender to desired position
            moveDefender(p, result[0], result[1]);
        }
    }
}

/** Move the defender in the correct decision */
void Match::moveDefender(Player *p, int destPosX, int destPosY)
{
    int moveDirection = 4, posX = p->getPosX(), posY = p->getPosY();
    //find the direction to move the defender
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

    //if the defender is not staying in the same position
    //check if they are screened
    if(moveDirection != 4)
    {
        //loop through all offensive players
        for(int i = 1; i < 6; i++)
        {
            Player *opp = teams[getOtherTeam(p->getTeam())]->getPlayer(i);
            //if in the same position as the defender
            if(opp->getPosX() == posX && opp->getPosY() == posY)
            {
                //calculate chance of a screen
                int screenRand = rand() % 5;

                if(screenRand == 0)
                {
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
/** Function to calculate if a block occurs */
bool Match::block(Player *p)
{
    int x = p->getPosX(), y = p->getPosY();
    //loop through all defenders
    for(int i = 1; i < 6; i++)
    {
        Player *opp = teams[getOtherTeam(p->getTeam())]->getPlayer(i);
        //check if the defender is in the same position
        if(opp->getPosX() == x && opp->getPosY() == y)
        {
            //calculate chance of a block occurring
            int block = rand() % 175;

            if(block < (opp->getBlock() * (opp->getBlock() / 4)))
            {
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

/** Function to simulate the result of a block */
void Match::blockedShot(int posX, int posY)
{
    //calculate the position of the ball
    int randX = (rand() % 3) + (posX - 1), randY = (rand() % 3) + (posY - 1);

    //if the ball went out of bounds, set up the inbound
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
            //find the players in who can pick up the ball after a block
            for(auto &player: orderOfPlay)
            {
                //loop through players and the positions of the ball
                for(int i = startX; i <= endX; i++)
                {
                    for(int j = startY; j <= endY; j++)
                    {
                        //store a player if they are in the same square
                        if(player->getPosX() == i && player->getPosY() == j)
                        {
                            probs.addProbability(player->getDefRebound());
                            players.push_back(player);
                            count++;
                        }
                    }
                }

            }
            //if no player found update the range
            startX-=1;
            endX+=1;
            startY-=1;
            endY+=1;
        }while(count == 0);

        //get the player who wins the ball
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
         //if the defenders get it, change possession
         if(ball.getTeam() != p->getTeam())
         {
             shotClock = 0;
             swapSides(p->getNumber());
         }
    }
}

/** Function to calculate a steal */
void Match::steal(Player *p)
{
    //calculate steal probability
    int stealRand = rand() % 400, steal = p->getSteal();

    //if steal occurrs
    if(stealRand < steal)
    {
        printValue("Steal", p->getNumber());
        p->getStatList()->addSteal();
        guiUpdateStat();

        swapSides(p->getNumber());
    }
    else if(stealRand <= 25)
    {
        //if foul occurs on the steal
        printValue("Illegal Contact", p->getNumber());
        fouls.addFoul(p->getTeam(), time);

        //if in bonus range, shoot free throws
        if(fouls.getTeamBonus(p->getTeam()) == true)
        {
            shootFreeThrow(p, 2);
        }
        else
        {
            setUpOffensiveInbound();
        }
    }
}


//==============================

/** Function to print the court using numerical values */
void Match::printCourt()
{
    //array represents court positions
    int court[8][14];
    //init the court values to 0
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 14; j++)
        {
            court[i][j] = 0;
        }
    }

    //add team one players to the array
    for(int j =1; j < 6; j++)
    {
        Player *p = teamOne->getPlayer(j);
        cout << j << " " << p->getPosY() << " " << p->getPosX() << endl;
        court[p->getPosY()][p->getPosX() + 7] = j+10;
    }

    //add team two players to the array
    for(int j =1; j < 6; j++)
    {
        Player *p = teamTwo->getPlayer(j);
        cout << j << " " << p->getPosY() << " " << p->getPosX() << endl;
        court[p->getPosY()][p->getPosX() + 7] = j+20;
    }

    //loop through the court array
    for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 14; j++)
            {
                //print each position with leading 2 digits and leading 0s
               printf("%02i ", court[i][j]);
            }
            cout << endl;
        }
    cout << endl;
}
