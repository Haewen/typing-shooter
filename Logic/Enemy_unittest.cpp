#include <gtest/gtest.h>
#include "Enemy.h"

TEST(Enemy, isDead) {
    Position testPos = Position(10,10);
    Enemy enemy = Enemy("", testPos, testPos, 10,20);
    EXPECT_FALSE(enemy.isDead());
}
