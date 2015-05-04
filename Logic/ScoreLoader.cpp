#include "ScoreLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <iostream>

struct score_coparator
{
    inline bool operator() (const Score& struct1, const Score& struct2)
    {
        return (struct1.value > struct2.value);
    }
};

ScoreLoader::ScoreLoader()
{
    std::fstream file(scoreFileName, std::fstream::in);
    std::string name;
    int value;
    while (file >> name >> value){
        Score score = Score{name,value};
        scores.push_back(score);
    }
    std::sort(scores.begin(), scores.end(), score_coparator());
    scores.resize(10);
}

std::vector<Score> ScoreLoader::getTopScore(){
    return scores;
}

void ScoreLoader::saveScore(std::string name, int score){
    std::fstream file(scoreFileName, std::fstream::app);
    file << name << " " << score << std::endl;
    file.close();
}