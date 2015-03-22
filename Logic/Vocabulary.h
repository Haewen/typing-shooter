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

enum Difficulty
{
	Easy,Medium,Hard
};

class Vocabulary
{
public:
	Vocabulary() = default;
	~Vocabulary();
	Vocabulary(std::string filename);
	std::string getRandomWord(Difficulty d=Easy);

private:
    std::ifstream easy,medium,hard;
	int easyCount, mediumCount, hardCount;
	std::string gotoLine(std::ifstream& file, int num);
};

#endif //VOCABULARY_H