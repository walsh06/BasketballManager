#include "Player.h"

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
Player::Player(map<string, string> playerMap)
{
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
    position = NULL;
    strategy = NULL;
}

//=================================
// Actions
//=================================

void Player::movePlayer(int direction)
{
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

void Player::calcHeatMap()
{
    int heatMap[8][7];

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
    int rating;
    if(dunk > layup)
    {
        rating = dunk;
    }
    else
    {
        rating = layup;
    }
    for(int i = 5; i < 7; i++)
    {
        heatMap[3][i] = (rating/heatFactor) + 1;
        heatMap[4][i] = (rating/heatFactor) + 1;
    }

    posValueMap.setMap(heatMap);
}

int Player::getPosValue(int x, int y)
{
    //posValueMap.getValue(x, y);
    return finalMap.getValue(x, y);
}

int Player::getPosValue()
{
    //posValueMap.getValue(posX, posY);
    return finalMap.getValue(posX, posY);
}

void Player::setPlayingPosition(PlayerPosition *pos)
{
    position = pos;
    updateMap();
}

void Player::setStrategy(PlayerStrategy *strategy)
{
    delete this->strategy;
    this->strategy = strategy;
    updateMap();
}

ProbabilityVector Player::getStrategyVector()
{
    return strategy->getWithBallVector();
}

void Player::updateMap()
{
    finalMap = posValueMap;
    if(position != NULL)
    {
        finalMap = finalMap + position->getMap();
    }
    if(strategy != NULL)
    {
        finalMap = finalMap + strategy->getMap();
        finalMap.printHeatMap();
    }
}

//======================================

//=================================
// Energy
//=================================

int Player::getEnergy()
{
    return energy;
}

int Player::getStamina()
{
    return stamina;
}

void Player::updateEnergy(bool playing)
{
    if(playing)
    {
        energy -= (2 + (20 - stamina)/2);
        playerStats.addMinute();
    }
    else
    {
        energy += 5;
        if(energy > 100)
        {
            energy = 100;
        }
    }
}

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

//==================================
// GETTERS AND SETTERS
//==================================
int Player::getPosX()
{
    return posX;
}

int Player::getPosY()
{
    return posY;
}

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

void Player::setRandomPos()
{
    setPos(rand() % 7, rand() % 8);
}

int Player::getNumber()
{
    return number;
}

int Player::getThreeShot()
{
    return threeShot;
}

int Player::getMediumShot()
{
    return mediumShot;
}

int Player::getCloseShot()
{
    return closeShot;
}

int Player::getDunk()
{
    return dunk;
}

int Player::getLayup()
{
    return layup;
}

int Player::getSteal()
{
    return steal;
}

int Player::getRange()
{
    int range = 5;

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

void Player::setTeam(int team)
{
    if(team == 1 || team == 2)
    {
        this->team = team;
    }
}

int Player::getTeam()
{
    return team;
}

int Player::getOffRebound()
{
    return offRebound;
}

int Player::getDefRebound()
{
    return defRebound;
}

int Player::getFreethrow()
{
    return freethrow;
}

int Player::getBlock()
{
    return block;
}

int Player::getSpeed()
{
    return speed;
}

int Player::getUnderBasketShot()
{
    return layup > dunk ? layup : dunk;
}

int Player::getPass()
{
    return pass;
}

int Player::getDefence()
{
    return defence;
}

StatList* Player::getStatList()
{
    return &playerStats;
}

//======================================
// Drive Basket
//======================================
bool Player::isDribbleDrive()
{
    return dribbleDrive;
}

void Player::setDribbleDrive(bool drive)
{
    dribbleDrive = drive;
}
