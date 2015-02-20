#include <gtest/gtest.h>
#include "Team.h"

TEST(TeamTest, PlayerPositionTest)
{
    Team team("Test");

    ASSERT_EQ(team.getPlayersInPosition(1,1).size(), 0);
    team.getPlayer(1)->setPos(1,1);
    ASSERT_EQ(team.getPlayersInPosition(1,1).size(), 1);
    team.getPlayer(2)->setPos(1,1);
    ASSERT_EQ(team.getPlayersInPosition(1,1).size(), 2);
}

TEST(TeamTest, PlayersUnderBasketTest)
{
    Team team("Test");
    ASSERT_EQ(team.getPlayersUnderBasket(), 0);
    team.getPlayer(1)->setPos(5,4);
    ASSERT_EQ(team.getPlayersUnderBasket(), 1);
    team.getPlayer(2)->setPos(5,4);
    ASSERT_EQ(team.getPlayersUnderBasket(), 2);
}
