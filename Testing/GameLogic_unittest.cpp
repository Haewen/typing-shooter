#include <gtest/gtest.h>
#include "GameLogic.h"

TEST(GameLogic, newGame) {
    GameLogic l = GameLogic();
    l.newGame();
    
    EXPECT_FALSE(l.isGameOver());
    EXPECT_FALSE(l.isWaveOver());
    EXPECT_EQ(0, l.getScore());
    EXPECT_EQ(5, l.getEnemyCount());
    EXPECT_EQ(1, l.getWaveCount());
}

TEST(GameLogic, update){
    GameLogic l = GameLogic();
    l.newGame();
    
    for (int i = 0; i < l.getEnemyCount(); i++)
    {
        Enemy aEnemy = l.getEnemies()[i];
        for(int j=0; j < aEnemy.getText().length(); j++)
        {
            // Missile minden enemy minden karakterehez
            l.getMissiles().push_back(Missile(l.getPlayerPosition(),&aEnemy));
        }
    }
    
    EXPECT_FALSE(l.isWaveOver());
    
    while(!l.isWaveOver()){
        // Frissites ameddig nincs vege a hullamnak
        l.update(0.01);
    }
    
    EXPECT_TRUE(l.isWaveOver());
}