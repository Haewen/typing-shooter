#ifndef SCORE_LOADER_H
#define SCORE_LOADER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

struct Score {
    std::string name;
    int value;
};

class ScoreLoader
{
public:
    ScoreLoader();
    std::vector<Score> getTopScore();
    void saveScore(std::string name, int score);
private:
    std::string scoreFileName = "defaultScores.txt";
    std::vector<Score> scores;
};

#endif //SCORE_LOADER_H