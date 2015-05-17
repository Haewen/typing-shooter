#include <gtest/gtest.h>
#include "GameLogic.h"

TEST(GameLogic, newGame) {
    GameLogic l = GameLogic();
    l.newGame();
    EXPECT_FALSE(l.isGameOver());
}