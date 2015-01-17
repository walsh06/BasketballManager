#ifndef FOULS_H
#define FOULS_H

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
