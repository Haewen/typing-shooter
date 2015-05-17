#include <gtest/gtest.h>
#include "Vocabulary.h"

TEST(Vocabulary, getRandomWord) {
    Vocabulary* vocabulary = new Vocabulary("Words/en");
    std::string text = vocabulary->getRandomWord(Difficulty::Hard);
    std::cout << "[          ] random test word = " << text << std::endl;
    EXPECT_GT(text.length(), 0);
}