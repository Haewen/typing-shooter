#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <vector>
#include <fstream>

/**
@brief An enumarator for difficulties.
*/
enum Difficulty
{
	Easy,Medium,Hard
};

/**
@brief Provides an interface for the logic to get words from a file.
@authors Benjamin Ferenc Hajas, Daniel Eke
*/
class Vocabulary
{
public:
	/**
	@brief Creates a new Vocabulary.
	@param filename	Name of the file to read the words from.
	*/
	Vocabulary(std::string filename);
	/**
		@brief Returns a random word.
		@param d	The difficulty of the returned word. (It's easy by default!)
	*/
	std::string getRandomWord(Difficulty d=Easy);

private:
    std::ifstream easy,medium,hard;
	int easyCount, mediumCount, hardCount;
	std::string gotoLine(std::ifstream& file, int num);
};

#endif //VOCABULARY_H