#pragma once
#include <string>
#include <vector>

class Vocabulary
{
public:
	Vocabulary(){ };
	Vocabulary(const char* filename);
	std::string getRandomWord();
	//For testing
	std::string Vocabulary::operator[](int n);
private:
	std::vector<std::string> words;
	int wordCount;
};

