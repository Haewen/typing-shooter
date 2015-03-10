#include "Vocabulary.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Vocabulary::Vocabulary(const char* filename)
{
	srand(time(NULL));
	std::ifstream file(filename);
	std::string word;
	int i = 0;
	while (std::getline(file, word)){
	words.push_back(word); ++i;
	if(i%5000==0)printf("%d \n", i);
	}
	wordCount = words.size();
}

std::string Vocabulary::getRandomWord()
{
	int random = rand() % wordCount;
	return words[random];
}

std::string Vocabulary::operator[](int n){
	return words[n];
}