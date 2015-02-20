#include "StatList.h"
#include <gtest/gtest.h>

TEST(StatListTest, PointsTest)
{
    StatList stats;
    stats.addGame();
    ASSERT_EQ(stats.getPointsPerGame(), 0.0);

    stats.addPoint();
    ASSERT_EQ(stats.getPointsPerGame(), 1.0);

    stats.addTwoPoints();
    ASSERT_EQ(stats.getPointsPerGame(), 3.0);

    stats.addMiss();
    ASSERT_EQ(stats.getPointsPerGame(), 3.0);

    stats.addThreePoints();
    ASSERT_EQ(stats.getPointsPerGame(), 6.0);
}

TEST(StatListTest, FieldGoalsTest)
{
    StatList stats;
    stats.addGame();

    ASSERT_EQ(stats.getFieldGoalsMade(), 0);
    ASSERT_EQ(stats.getShots(), 0);

    stats.addPoint();
    ASSERT_EQ(stats.getFieldGoalsMade(), 0);
    ASSERT_EQ(stats.getShots(), 0);

    stats.addTwoPoints();
    ASSERT_EQ(stats.getFieldGoalsMade(), 1);
    ASSERT_EQ(stats.getShots(), 1);

    stats.addThreePoints();
    ASSERT_EQ(stats.getFieldGoalsMade(), 2);
    ASSERT_EQ(stats.getShots(), 2);

    stats.addMiss();
    ASSERT_EQ(stats.getFieldGoalsMade(), 2);
    ASSERT_EQ(stats.getShots(), 3);
}

TEST(StatListTest, ThreePointTest)
{
    StatList stats;
    stats.addGame();

    ASSERT_EQ(stats.getThreeShots(), 0);
    ASSERT_EQ(stats.getThreeShootingPercentage(), 0);

    stats.addThreePoints();

    ASSERT_EQ(stats.getThreeShots(), 1);
    ASSERT_EQ(stats.getThreeShootingPercentage(), 1.0);

    stats.addThreeMiss();

    ASSERT_EQ(stats.getThreeShots(), 2);
    ASSERT_EQ(stats.getThreeShootingPercentage(), 0.5);
}

TEST(StatListTest, ReboundsTest)
{
    StatList stats;
    stats.addGame();

    ASSERT_EQ(stats.getRebounds(), 0);

    stats.addOffensiveRebound();
    ASSERT_EQ(stats.getRebounds(), 1);

    stats.addDefensiveRebound();
    ASSERT_EQ(stats.getRebounds(), 2);
}

TEST(StatListTest, AssistTest)
{
    StatList stats;
    stats.addGame();

    ASSERT_EQ(stats.getAssists(), 0);

    stats.addAssist();
    ASSERT_EQ(stats.getAssists(), 1);
}

TEST(StatListTest, FreeThrowTest)
{
    StatList stats;
    stats.addGame();

    ASSERT_EQ(stats.getFreeThrowPercentage(), 0);

    stats.addFreeThrowScore();
    ASSERT_EQ(stats.getFreeThrowPercentage(), 1.0);

    stats.addFreeThrow();
    ASSERT_EQ(stats.getFreeThrowPercentage(), 0.5);
}
