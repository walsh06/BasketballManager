#ifndef BALL_H
#define BALL_H

/* Used to store the data of the ball during simulation. Tracks the
 * player and team who currently has possession. Provides methods to
 * easily swap teams if possession changes
 */
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

private:
    int player, team;
};

#endif // BALL_H
