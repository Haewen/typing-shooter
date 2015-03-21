/**
Provides an interface for the logic to get words from a file.
@author Benjamin Ferenc Hajas
@credits Dániel Eke
*/

#include "Vocabulary.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <iostream>

Vocabulary::Vocabulary(const char* filename)
{
	srand(time(NULL));
    file.open(filename);
}

std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

std::string Vocabulary::getRandomWord()
{
	int random = rand() % wordCount;
    GotoLine(file, random);
    
    std::string randomLine;
    file >> randomLine;
    //std::cout << randomLine;
	return randomLine;
}

std::string Vocabulary::operator[](int n){
	//return words[n];
    // TODO
    return "";
}