#include <gtest/gtest.h>
#include "Fouls.h"
TEST(FoulTest, TestTeamOneBonus)
{
    Fouls fouls;
    for(int i = 0; i < 5; i++)
    {
        ASSERT_EQ(fouls.isTeamOneBonus(), false);
        fouls.addFoul(1, 600);
    }
    ASSERT_EQ(fouls.isTeamOneBonus(), true);
}


TEST(FoulTest, TestTeamTwoBonus)
{
    Fouls fouls;
    for(int i = 0; i < 5; i++)
    {
        ASSERT_EQ(fouls.isTeamTwoBonus(), false);
        fouls.addFoul(2, 600);
    }
    ASSERT_EQ(fouls.isTeamTwoBonus(), true);
}

TEST(FoulTest, TestTeamOneEndPeriodBonus)
{
    Fouls fouls;
    ASSERT_EQ(fouls.isTeamOneBonus(), false);
    fouls.addFoul(1, 20);
    ASSERT_EQ(fouls.isTeamOneBonus(), false);
    fouls.addFoul(1, 20);
    ASSERT_EQ(fouls.isTeamOneBonus(), true);
}

TEST(FoulTest, TestTeamTwoEndPeriodBonus)
{
    Fouls fouls;
    ASSERT_EQ(fouls.isTeamTwoBonus(), false);
    fouls.addFoul(2, 20);
    ASSERT_EQ(fouls.isTeamTwoBonus(), false);
    fouls.addFoul(2, 20);
    ASSERT_EQ(fouls.isTeamTwoBonus(), true);
}
