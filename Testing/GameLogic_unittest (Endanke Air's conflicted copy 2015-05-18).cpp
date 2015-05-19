#include <gtest/gtest.h>
#include "GameLogic.h"

TEST(GameLogic, newGame) {
    GameLogic l = GameLogic();
    l.newGame();
    
    EXPECT_FALSE(l.isGameOver());
    EXPECT_EQ(0, l.getScore());
    EXPECT_EQ(5, l.getEnemyCount());
    EXPECT_EQ(1, l.getWaveCount());
}

TEST(GameLogic, update){
    GameLogic l = GameLogic();
    l.newGame();
    
    l.update(0.01);
    // TODO: ezt
}