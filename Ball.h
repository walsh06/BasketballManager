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

private:
    int player, team;
};

#endif // BALL_H
