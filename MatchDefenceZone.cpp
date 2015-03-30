#include "MatchDefenceZone.h"

/** MatchDefenceZone Constructor */
MatchDefenceZone::MatchDefenceZone(Team *teamOne, Team *teamTwo):MatchDefence(teamOne, teamTwo)
{
}

/** Get the position for a defender to move to in zone defence*/
int* MatchDefenceZone::moveZoneDefence(Player *p, Ball *ball)
{
    //get starting values for calculation
    Team *team = teams[p->getTeam() - 1], *otherTeam = teams[getOtherTeam(p->getTeam())];
    int pos = team->getPlayerPosition(p->getNumber()), ballPos = ball->getPlayerPosition();
    Player *ballCarrier = otherTeam->getPlayer(ballPos);
    int ballX = ballCarrier->getPosX(), ballY = ballCarrier->getPosY();
    int defenceSetting = team->getDefenceSetting(ballPos);

    int destX, destY;

    //check which position the defender is
    //different calculations for each position
    //uses the ball position to decide the desired court position to move to
    if(pos == 1)
    {
        if((ballX == 2 || ballX == 3) && (ballY == 3 || ballY == 4))
        {
            moveDefenceTight(p, ballCarrier);
        }
        else if(((ballX == 1 && (ballY < 6 && ballY > 1)) || (ballX == 2 && (ballY < 6 && ballY > 1))) && (defenceSetting == Team::TIGHT))
        {
            moveDefenceTight(p, ballCarrier);
        }
        else
        {
            if(ballX < 4)
            {
                if(ballY < 3)
                {
                    destX = 2; destY = 3;
                }
                else
                {
                    destX = 2; destY = 4;
                }
            }
            else
            {
                if(ballY < 3)
                {
                    destX = 3; destY = 3;
                }
                else
                {
                    destX = 3; destY = 4;
                }
            }
            int result[2] = {destX, destY};
            return result;
        }
    }
    else if(pos == 2 || pos == 3)
    {
        if(pos == 3)
        {
            ballY = flipY(ballY);
        }
        if(ballX < 2)
        {
            destX = 3; destY = 5;
        }
        else if(ballY < 4)
        {
            destY = 4;
            if(ballX > 3)
            {
                destX = 4;
            }
            else
            {
                destX = 3;
            }
        }
        else if(ballX > 4)
        {
            destX = 4;
            if(ballY == 7)
            {
                destY = 6;
            }
            else
            {
                destY = ballY;
            }
        }
        else if(ballY == 7 && ballX == 4)
        {
            destX = ballX;
            if(defenceSetting == Team::TIGHT)
            {
                destY = ballY;
            }
            else
            {
                destY = 6;
            }
        }
        else if((ballX == 2 && ballY == 6) || (ballX == 2 && ballY == 7) || (ballX == 3 && ballY == 7))
        {
            if(defenceSetting == Team::TIGHT)
            {
                destX = ballX; destY = ballY;
            }
            else
            {
                destX = 3; destY = 6;
            }
        }
        else
        {
             destX = ballX; destY = ballY;
        }
        if(pos == 3)
        {
            destY = flipY(destY);
        }
        int result[2] = {destX, destY};
        return result;
    }
    else if(pos == 4 || pos == 5)
    {
        if(pos == 5)
        {
            ballY = flipY(ballY);
        }
        if(ballX < 3)
        {
            destX = 5; destY = 5;
        }
        else if(ballY < 4)
        {
            destY = 4;
            if(ballX == 6)
            {
                destX = 6;
            }
            else
            {
                destX = 5;
            }
        }
        else if(ballX < 4)
        {
            destX = 5; destY = 5;
        }
        else if(ballX < 5)
        {
            destX = 5;
            if(ballY == 4)
            {
                destY = 4;
            }
            else if(ballY == 5)
            {
                destY = 5;
            }
            else
            {
                destY = 6;
            }
        }
        else if(ballY == 7)
        {
            destX = ballX;
            if(defenceSetting == Team::TIGHT)
            {
                destY = ballY;
            }
            else
            {
                destY = 6;
            }
        }
        else
        {
            destX = ballX; destY = ballY;
        }

        if(pos == 5)
        {
            destY = flipY(destY);
        }
        int result[2] = { destX, destY};
        return result;
    }
}

/** Invert the y position value across the centre of the court */
int MatchDefenceZone::flipY(int y)
{
    int newY;
    if(y < 4)
    {
        newY = y + (((3-y) * 2) + 1);
    }
    else
    {
        newY = y - (((y - 4) * 2) + 1);
    }
    return newY;
}
