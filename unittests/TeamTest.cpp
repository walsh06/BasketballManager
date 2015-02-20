#include <gtest/gtest.h>
#include "Team.h"

TEST(TeamTest, PlayerPositionTest)
{
    Team team("Test");

    ASSERT_EQ(team.getPlayersInPosition(0,0).size(), 0);
    team.getPlayer(1)->setPos(0,0);
    ASSERT_EQ(team.getPlayersInPosition(0,0).size(), 1);


}
