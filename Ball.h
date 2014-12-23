#ifndef BALL_H
#define BALL_H

class Ball
{
public:
    Ball();
    int getPlayerNumber();
    int getTeam();
    void setPlayerNumber(int num);
    void setTeam(int team);

private:
    int playerNumber, team;
};

#endif // BALL_H
