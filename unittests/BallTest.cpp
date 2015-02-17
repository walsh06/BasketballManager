#include <gtest/gtest.h>
#include "Ball.h"
TEST(BallTest, BallSetTeamTest)
{
    Ball ball;
    ball.setTeam(1);
    ASSERT_EQ(ball.getTeam(), 1);
    ball.changeTeam();
    ASSERT_EQ(ball.getTeam(), 2);
}


TEST(BallTest, BallSetPlayerTest)
{
    Ball ball;
    ball.setPlayerPosition(1);
    ASSERT_EQ(ball.getPlayerPosition(), 1);
    ball.setPlayerPosition(2);
    ASSERT_EQ(ball.getPlayerPosition(), 2);
}
