/**
	Provides an interface for the logic to load high scores from a file.
	@author Dániel Eke
    @credits Benjamin Ferenc Hajas
*/

#include "ScoreLoader.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <iostream>
#include <algorithm>

struct score_coparator
{
    inline bool operator() (const Score& struct1, const Score& struct2)
    {
        return (struct1.value > struct2.value);
    }
};

ScoreLoader::ScoreLoader()
{
    loadScores();
}

ScoreLoader::ScoreLoader(std::string filename)
{
    scoreFileName = filename;
    loadScores();
}

void ScoreLoader::loadScores(){
    std::fstream file(scoreFileName.c_str(), std::fstream::in);
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
    std::fstream file(scoreFileName.c_str(), std::fstream::app|std::fstream::out);
    file << name << " " << score << std::endl;
    file.close();
}