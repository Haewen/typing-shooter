/**
	Provides an interface for the logic to get words from a file.
	@author Benjamin Ferenc Hajas
	@credits Dániel Eke
*/

#ifndef VOCABULARY_H
#define VOCABULARY_H

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

#endif //VOCABULARY_H