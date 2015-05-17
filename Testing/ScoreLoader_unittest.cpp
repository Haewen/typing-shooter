#include <gtest/gtest.h>
#include "ScoreLoader.h"

TEST(ScoreLoader, scoreSaving){
    ScoreLoader scoreLoader = ScoreLoader("tempScores.txt");
    scoreLoader.saveScore("TestPlayer", 100);
}

TEST(ScoreLoader, getTopScores) {
    ScoreLoader scoreLoader = ScoreLoader("tempScores.txt");
    std::vector<Score> scoreData = scoreLoader.getTopScore();
    EXPECT_GT(scoreData.size(), 0);
}