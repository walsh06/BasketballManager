#ifndef BALL_H
#define BALL_H

class Ball
{
public:
    Ball();
    int getPlayerPosition();
    int getTeam();
    void setPlayerPosition(int num);
    void setTeam(int team);
    void changeTeam();
    void changeTeam(int team);
    int getPosX();
    int getPosY();
    void setPos(int x, int y);
private:
    int player, team;
    int posX, posY;
};

#endif // BALL_H
