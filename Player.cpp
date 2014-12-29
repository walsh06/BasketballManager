#include "Player.h"

Player::Player(int number)
{
    this->number = number;

    threeShot = 13;
    mediumShot = 18;
    closeShot = 9;
    dunk = 4;
    layup = 12;
    offRebound = 10;
    defRebound = 10;
    freethrow = 15;
    block = 15;
    speed = rand() % 21;

    calcHeatMap();
    //printHeatMap();
    setRandomPos();
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
    for(int i = 2; i < 7; i++)
    {
        heatMap[0][i] = (threeShot/heatFactor + 1);
        heatMap[7][i] = (threeShot/heatFactor + 1);
    }

    for(int i = 0; i < 8; i++)
    {
        heatMap[i][0] = (threeShot/4)/heatFactor + 1;
        heatMap[i][1] = threeShot/heatFactor + 1;

    }
    //=================================
    //Medium shot mapping
    for(int i = 2; i < 7; i++)
    {
        heatMap[1][i] = (mediumShot/heatFactor) + 1;
        heatMap[6][i] = (mediumShot/heatFactor) + 1;
        if( i == 2 || i == 3)
        {
            heatMap[2][i] =  (mediumShot/heatFactor) + 1;
            heatMap[3][i] =  (mediumShot/heatFactor) + 1;
            heatMap[4][i] =  (mediumShot/heatFactor) + 1;
            heatMap[5][i] =  (mediumShot/heatFactor) + 1;
        }
    }
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
    posValueMap.getValue(x, y);
}

int Player::getPosValue()
{
    posValueMap.getValue(posX, posY);
}

//======================================


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

int Player::getRange()
{
    int range = -1;

    if(posX == 0 || posX == 1)
    {
        range = 4;
    }
    else if(posX == 2 || posX == 3)
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

//======================================

