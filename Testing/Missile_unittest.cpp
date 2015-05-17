#include <gtest/gtest.h>
#include "Missile.h"
#include "Enemy.h"

TEST(Missile, loadAndShoot) {
    Position enemyTestPos = Position(10,10);
    Position playerTestPos = Position(10,0);

    Enemy enemy = Enemy("", enemyTestPos, playerTestPos, 10,20);
    Missile missile = Missile(playerTestPos, &enemy);
    
    EXPECT_FALSE(missile.isDead());
    EXPECT_FALSE(enemy.isDead());

    EXPECT_LT(missile.getPosition().distance(playerTestPos),
              enemy.getPosition().distance(playerTestPos));
    EXPECT_EQ(0, missile.getPosition().getY());
    
    missile.update(0.2);
    
    EXPECT_GT(missile.getPosition().distance(playerTestPos),
              enemy.getPosition().distance(playerTestPos));
}