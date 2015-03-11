#pragma once
#include <string>
#include <vector>
#include <fstream>

class Vocabulary
{
public:
	Vocabulary() = default;
	Vocabulary(const char* filename);
	std::string getRandomWord();
	//For testing
	std::string operator[](int n);
private:
    // fájl sorainak száma
    const static int wordCount = 58110;
    std::fstream file;
};