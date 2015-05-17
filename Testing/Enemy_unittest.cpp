#include <gtest/gtest.h>
#include "Enemy.h"
#include <string>

TEST(Enemy, defaultValues) {
    Position testPos = Position(10,10);
    Enemy enemy = Enemy("", testPos, testPos, 10, 20);
    
    EXPECT_FALSE(enemy.isDead());
    EXPECT_FALSE(enemy.isExploded());
    EXPECT_TRUE(enemy.onScreen());
    EXPECT_EQ(0, enemy.getText().length());
}