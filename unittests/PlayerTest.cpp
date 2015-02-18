#include "Player.h"
#include "PlayerStrategyBalanced.h"
#include "PlayerStrategyBalancedPlaymaker.h"
#include "PositionPointGuard.h"
#include "PositionCentre.h"
#include <gtest/gtest.h>

TEST(PlayerTest, PlayerMoveTest)
{
    Player player;
    player.setPos(4, 4);
    ASSERT_EQ(player.getPosX(), 4);
    ASSERT_EQ(player.getPosY(), 4);

    player.movePlayer(0);
    ASSERT_EQ(player.getPosX(), 3);
    ASSERT_EQ(player.getPosY(), 3);
    player.movePlayer(1);
    ASSERT_EQ(player.getPosX(), 3);
    ASSERT_EQ(player.getPosY(), 2);
    player.movePlayer(2);
    ASSERT_EQ(player.getPosX(), 4);
    ASSERT_EQ(player.getPosY(), 1);
    player.movePlayer(3);
    ASSERT_EQ(player.getPosX(), 3);
    ASSERT_EQ(player.getPosY(), 1);
    player.movePlayer(4);
    ASSERT_EQ(player.getPosX(), 3);
    ASSERT_EQ(player.getPosY(), 1);
    player.movePlayer(5);
    ASSERT_EQ(player.getPosX(), 4);
    ASSERT_EQ(player.getPosY(), 1);
    player.movePlayer(6);
    ASSERT_EQ(player.getPosX(), 3);
    ASSERT_EQ(player.getPosY(), 2);
    player.movePlayer(7);
    ASSERT_EQ(player.getPosX(), 3);
    ASSERT_EQ(player.getPosY(), 3);
    player.movePlayer(8);
    ASSERT_EQ(player.getPosX(), 4);
    ASSERT_EQ(player.getPosY(), 4);
}

TEST(PlayerTest, PlayerRangeTest)
{
    Player player;
    player.setPos(0, 0);
    ASSERT_EQ(player.getRange(), 4);
    player.setPos(1, 1);
    ASSERT_EQ(player.getRange(), 4);
    player.setPos(2, 2);
    ASSERT_EQ(player.getRange(), 4);
    player.setPos(3, 3);
    ASSERT_EQ(player.getRange(), 3);
    player.setPos(4, 4);
    ASSERT_EQ(player.getRange(), 2);
    player.setPos(5, 4);
    ASSERT_EQ(player.getRange(), 1);
}

TEST(PlayerTest, PlayerEnergyTest)
{
    Player player;
    int stamina = player.getStamina(), energyLoss = 2 + (20 - stamina)/2;
    ASSERT_EQ(player.getEnergy(), 100);
    player.updateEnergy(true);
    ASSERT_EQ(player.getEnergy(), 100 - energyLoss);
    player.updateEnergy(true);
    ASSERT_EQ(player.getEnergy(), 100 - (energyLoss * 2));
    player.updateEnergy(false);
    ASSERT_EQ(player.getEnergy(), 100 - (energyLoss * 2) + 5);
    player.updateEnergy(false);
    ASSERT_EQ(player.getEnergy(), 100);
}

TEST(PlayerTest, PlayerStrategyTest)
{
    Player player;
    player.setStrategy(new PlayerStrategyBalanced());
    int valueOne = player.getPosValue(1, 0);
    int valueTwo = player.getPosValue(3, 3);
    int valueThree = player.getPosValue(6,4);
    player.setStrategy(new PlayerStrategyBalancedPlaymaker());
    ASSERT_NE(valueOne, player.getPosValue(1, 0));
    ASSERT_NE(valueTwo, player.getPosValue(3, 3));
    ASSERT_NE(valueThree, player.getPosValue(6,4));
}

TEST(PlayerTest, PlayerPositionTest)
{
    Player player;
    player.setPlayingPosition(new PositionPointGuard());
    int valueOne = player.getPosValue(1, 0);
    int valueTwo = player.getPosValue(4, 3);
    int valueThree = player.getPosValue(6,4);
    player.setPlayingPosition(new PositionCentre());
    ASSERT_NE(valueOne, player.getPosValue(1, 0));
    ASSERT_NE(valueTwo, player.getPosValue(4, 3));
    ASSERT_NE(valueThree, player.getPosValue(6,4));
}

