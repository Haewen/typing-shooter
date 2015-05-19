#include "Vocabulary.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <iostream>

Vocabulary::Vocabulary(std::string filename)
{
	srand((int)time(NULL));
	easy.open((filename + "_easy").c_str());
	easyCount = (int)std::count(std::istreambuf_iterator<char>(easy), std::istreambuf_iterator<char>(), '\n');
	medium.open((filename + "_medium").c_str());
	mediumCount = (int)std::count(std::istreambuf_iterator<char>(medium), std::istreambuf_iterator<char>(), '\n');
	hard.open((filename + "_hard").c_str());
	hardCount = (int)std::count(std::istreambuf_iterator<char>(hard), std::istreambuf_iterator<char>(), '\n');
}

std::string Vocabulary::gotoLine(std::ifstream& file, int num){
    file.seekg(0,std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
	std::string line;
	file >> line;
	return line;
}

std::string Vocabulary::getRandomWord(Difficulty d)
{
	switch (d)
	{
		case Easy: return gotoLine(easy, rand() % easyCount);
		case Medium: return gotoLine(medium, rand() % mediumCount);
		case Hard: return gotoLine(hard, rand() % hardCount);
	}

	int random = rand() % easyCount;
	gotoLine(easy,random);
    std::string randomLine;
    easy >> randomLine;
	return randomLine;
}
