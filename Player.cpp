#include "Player.h"

/** Default constructor for a player */
Player::Player()
{
    energy = 100;
    stamina = 15;
    posX = 0;
    posY = 0;
    position = NULL;
    strategy = NULL;
}

/** Temporary Constructor used in early development */
Player::Player(int number)
{
    this->number = number;
    if(number > 3)
    {
        threeShot = 4;
        mediumShot = 4;
        closeShot = 18;
        dunk = 19;
        layup = 15;
        offRebound = 16;
        defRebound = 19;
        freethrow = 13;
        block = 15;
        speed = rand() % 21;
        steal = 6;
        pass = 18;
    }
    else
    {
        threeShot = 16;
        mediumShot = 19;
        closeShot = 9;
        dunk = 3;
        layup = 13;
        offRebound = 5;
        defRebound = 10;
        freethrow = 16;
        block = 12;
        speed = rand() % 21;
        steal = 15;
        pass = 12;
    }
    calcHeatMap();
    position = NULL;
    strategy = NULL;
}

/** Player constructor taking a map as a parameter containing the ratings of the player */
Player::Player(map<string, string> playerMap)
{
    //set the ratings of the player from the map
    this->name = playerMap["name"];
    this->number = stoi(playerMap["number"]);
    threeShot = stoi(playerMap["shootThree"]);
    mediumShot = stoi(playerMap["shootMid"]);
    closeShot = stoi(playerMap["shootClose"]);
    dunk = stoi(playerMap["dunk"]);
    layup = stoi(playerMap["layup"]);
    offRebound = stoi(playerMap["offRebound"]);
    defRebound = stoi(playerMap["defRebound"]);
    freethrow = stoi(playerMap["freeThrow"]);
    block = stoi(playerMap["block"]);
    speed = stoi(playerMap["speed"]);
    steal = stoi(playerMap["steal"]);
    pass = stoi(playerMap["pass"]);
    defence = stoi(playerMap["defence"]);
    energy = 100;
    stamina = stoi(playerMap["stamina"]);
    calcHeatMap();

    string pos = playerMap["pos"];
    position = NULL;
    strategy = NULL;

    //set the players position and load the position map
    if(pos == "PG")
    {
        playingPosition = 1;
        setPlayingPosition(new PositionPointGuard());
    }
    else if(pos == "SG")
    {
        playingPosition = 2;
        setPlayingPosition(new PositionShootingGuard());
    }
    else if(pos == "SF")
    {
        playingPosition = 3;
        setPlayingPosition(new PositionSmallForward());
    }
    else if(pos == "PF")
    {
        playingPosition = 4;
        setPlayingPosition(new PositionPowerForward());
    }
    else if(pos == "C")
    {
        playingPosition = 5;
        setPlayingPosition(new PositionCentre());
    }

    learning = false;
}

/** Player Destructor */
Player::~Player()
{
    delete strategy;
    delete position;
}

//=================================
// Actions
//=================================

/** Updates the players position in the directio provided */
void Player::movePlayer(int direction)
{
    /* 0 Up Left
     * 1 Up
     * 2 Up Right
     * 3 Left
     * 4 Stay
     * 5 Right
     * 6 Down Left
     * 7 Down
     * 8 Down Right
     */
    switch(direction)
    {
        case 0:
            setPos(posX - 1, posY - 1);
        break;
        case 1:
            setPos(posX, posY - 1);
        break;
        case 2:
            setPos(posX + 1, posY - 1);
        break;
        case 3:
            setPos(posX - 1, posY);
        break;
        case 4:
            setPos(posX, posY);
        break;
        case 5:
            setPos(posX + 1, posY);
        break;
        case 6:
            setPos(posX - 1, posY + 1);
        break;
        case 7:
            setPos(posX, posY + 1);
        break;
        case 8:
            setPos(posX + 1, posY + 1);
        break;
    }
    if(posX >= 0)
    {
        //moveTrackerMap.incrementValue(posX, posY);
    }
}


//=================================
// Heat Map
//=================================

/** Calculates the ability map of the player */
void Player::calcHeatMap()
{
    int heatMap[8][7];

    //init values to 0
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 7; j++)
        {
           heatMap[i][j]  = 0;
        }
    }
    //===============================
    //three shot heat mapping
    for(int i = 3; i < 7; i++)
    {
        heatMap[0][i] = (threeShot/heatFactor + 1);
        heatMap[7][i] = (threeShot/heatFactor + 1);
    }

    for(int i = 0; i < 8; i++)
    {
        heatMap[i][0] = (threeShot/4)/heatFactor + 1;
        heatMap[i][1] = threeShot/heatFactor + 1;
        if(i != 4 && i != 3)
        {
            heatMap[i][2] = threeShot/heatFactor + 1;
        }
    }
    //=================================
    //Medium shot mapping
    for(int i = 3; i < 7; i++)
    {
        heatMap[1][i] = (mediumShot/heatFactor) + 1;
        heatMap[6][i] = (mediumShot/heatFactor) + 1;
        if(i == 3)
        {
            heatMap[2][i] =  (mediumShot/heatFactor) + 1;
            heatMap[3][i] =  (mediumShot/heatFactor) + 1;
            heatMap[4][i] =  (mediumShot/heatFactor) + 1;
            heatMap[5][i] =  (mediumShot/heatFactor) + 1;
        }
    }
    heatMap[3][2] = (mediumShot/heatFactor) + 1;
    heatMap[4][2] = (mediumShot/heatFactor) + 1;
    //=================================
    //close shot mapping
    for(int i = 4; i < 7; i++)
    {
        heatMap[2][i] = (closeShot/heatFactor) + 1;
        heatMap[5][i] = (closeShot/heatFactor) + 1;
        if( i == 4)
        {
            heatMap[4][i] =  (closeShot/heatFactor) + 1;
            heatMap[3][i] =  (closeShot/heatFactor) + 1;
        }
    }
    //=================================
    //Dunk/layup shot mapping
    int rating = getUnderBasketShot();
    for(int i = 5; i < 7; i++)
    {
        heatMap[3][i] = (rating/heatFactor) + 1;
        heatMap[4][i] = (rating/heatFactor) + 1;
    }

    posValueMap.setMap(heatMap);
}

/** Get the influence value at position x, y */
int Player::getPosValue(int x, int y)
{
    return finalMap.getValue(x, y);
}

/** Get the influence value of the current position */
int Player::getPosValue()
{
    return finalMap.getValue(posX, posY);
}

/** Set the Playing position of the player */
void Player::setPlayingPosition(PlayerPosition *pos)
{
    //delete the old position and set the new one
    delete this->position;
    this->position = pos;

    updateMap();
}

/** Set the Strategy of the player */
void Player::setStrategy(PlayerStrategy *strategy)
{
    //delete the old strategy and set the new one
    delete this->strategy;
    this->strategy = strategy;
    updateMap();
}

/** Get the probability vector of the players strategy */
ProbabilityVector* Player::getStrategyVector()
{
    return strategy->getWithBallVector();
}

/** Get the players strategy */
PlayerStrategy* Player::getStrategy()
{
    return strategy;
}

/** Update the overall map by combining a players ability, position and strategy */
void Player::updateMap()
{
    //start with the ability map
    finalMap = posValueMap;

    //add the position map if it not null
    if(position != NULL)
    {
        finalMap = finalMap + position->getMap();
    }
    //add the strategy map if it not null
    if(strategy != NULL)
    {
        finalMap = finalMap + *strategy->getMap();
    }
}

//======================================

//=================================
// Energy
//=================================
/** Get the playing position */
int Player::getPlayingPosition()
{
    return playingPosition;
}

/** Return players current energy */
int Player::getEnergy()
{
    return energy;
}

/** Return a players stamina */
int Player::getStamina()
{
    return stamina;
}

/** Update a players energy */
void Player::updateEnergy(bool playing)
{
    if(playing)
    {
        //if they are playing lower energy by using stamina
        energy -= (2 + (20 - stamina)/2);
        playerStatsGame.addMinute();
    }
    else
    {
        //if they are not playing increase their energy
        energy += 5;
        if(energy > 100)
        {
            energy = 100;
        }
    }
}

/** Get the modifier when a player is tired */
int Player::getEnergyModifier()
{
   if(energy < 80)
   {
       return 16 - (energy / 5);
   }
   else
   {
       return 0;
   }
}

/** Reset a players energy to 100 */
void Player::resetEnergy()
{
    energy = 100;
}


//==================================
// GETTERS AND SETTERS
//==================================

/** Return a players x position */
int Player::getPosX()
{
    return posX;
}
/** Return a players y position */
int Player::getPosY()
{
    return posY;
}
/** Sets a players x and y position */
void Player::setPos(int x, int y)
{
    if(x >= -7 && x < 7)
    {
        posX = x;
    }
    if(y >= 0 && y < 8)
    {
        posY = y;
    }
}

/** Sets a random position in the half court */
void Player::setRandomPos()
{
    setPos(rand() % 7, rand() % 8);
}

/** Return a players number */
int Player::getNumber()
{
    return number;
}

/** Return three point rating */
int Player::getThreeShot()
{
    return threeShot;
}

/** Return medium shot rating */
int Player::getMediumShot()
{
    return mediumShot;
}

/** Return close shot rating */
int Player::getCloseShot()
{
    return closeShot;
}

/** Return dunk rating */
int Player::getDunk()
{
    return dunk;
}

/** Return layup rating */
int Player::getLayup()
{
    return layup;
}

/** Return steal rating */
int Player::getSteal()
{
    return steal;
}

/** Return current shooting range of the player */
int Player::getRange()
{
    int range = 5;
    /* 1 under basket
     * 2 Close
     * 3 Medium
     * 4 Three Point
     */
    if(posX == 0 || posX == 1)
    {
        range = 4;
    }
    else if(posX == 2)
    {
        if(posY > 2 && posY < 5)
        {
            range = 3;
        }
        else
        {
            range = 4;
        }
    }
    else if(posX == 3)
    {
        if(posY > 0 && posY < 7)
        {
            range = 3;
        }
        else
        {
            range = 4;
        }
    }
    else if(posX == 4)
    {
        if(posY >= 2 && posY <= 5)
        {
            range = 2;
        }
        else if(posY == 1 || posY == 6)
        {
            range = 3;
        }
        else
        {
            range = 4;
        }
    }
    else if(posX == 5 || posX == 6)
    {
        switch(posY)
        {
            case 0:case 7: range = 4; break;
            case 1: case 6: range = 3; break;
            case 2: case 5: range = 2; break;
            case 3: case 4: range = 1; break;
        }
    }
    return range;
}

/** Set the team of the player */
void Player::setTeam(int team)
{
    if(team == 1 || team == 2)
    {
        this->team = team;
    }
}

/** Return the team number of the player */
int Player::getTeam()
{
    return team;
}

/** Return offensive rebound rating */
int Player::getOffRebound()
{
    return offRebound;
}

/** Return defensive rebound rating */
int Player::getDefRebound()
{
    return defRebound;
}

/** Return free throw rating */
int Player::getFreethrow()
{
    return freethrow;
}

/** Return block rating */
int Player::getBlock()
{
    return block;
}

/** Return speed rating */
int Player::getSpeed()
{
    return speed;
}

/** Return best shot used under the basket, dunk or layup */
int Player::getUnderBasketShot()
{
    return layup > dunk ? layup : dunk;
}

/** Return pass rating */
int Player::getPass()
{
    return pass;
}

/** Return defence rating */
int Player::getDefence()
{
    return defence;
}

/** Return game stat list */
StatList* Player::getStatList()
{
    return &playerStatsGame;
}

/** Return season/career/overall stat list */
StatList* Player::getOverAllStatList()
{
    return &playerStatsOverAll;
}

/** Add game stats to overall stats */
void Player::updateOverAllStats()
{
    playerStatsOverAll = playerStatsOverAll + playerStatsGame;
}

/** Reset game stats to 0 */
void Player::resetGameStats()
{
    playerStatsGame.resetStats();
    playerStatsGame.addGame();
}

/** Return the players name */
string Player::getName()
{
    return name;
}

/** Return if the player is in learning mode */
bool Player::isLearning()
{
    return learning;
}

/** Set the players learning status */
void Player::setLearning(bool learn)
{
    learning = learn;
}

//======================================
// Drive Basket
//======================================
/** Return if the player is driving to the basket */
bool Player::isDribbleDrive()
{
    return dribbleDrive;
}

/** Set if the player is driving to the basket */
void Player::setDribbleDrive(bool drive)
{
    dribbleDrive = drive;
}
