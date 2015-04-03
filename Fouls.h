#ifndef FOULS_H
#define FOULS_H

/*Fouls is used to track fouls for the match. The rules can be changed in
 * here for how the bonus free throws occur in a game.
 */
class Fouls
{
public:
    Fouls();
    bool getTeamBonus(int team);
    bool isTeamOneBonus();
    bool isTeamTwoBonus();
    void addFoul(int team, int time);
    void resetFouls();

private:
    bool teamOneBonus, teamTwoBonus;
    int teamOneFouls, teamTwoFouls, teamOneEndPeriodFouls, teamTwoEndPeriodFouls;
};

#endif // FOULS_H
