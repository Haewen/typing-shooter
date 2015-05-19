#ifndef SCORE_LOADER_H
#define SCORE_LOADER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

/**
	@brief Small struct to represent a score with a name and a value.
	Small class to represent a score with a name and a value.
*/
struct Score {
    std::string name;
    int value;
};

/**
	@brief Compares two scores.
*/
struct score_coparator
{	/**
		@brief Compares two scores.
		@returns the first score if the first score is bigger.
		@return the second score otherwise.
	*/
	inline bool operator() (const Score& struct1, const Score& struct2)
	{
		return (struct1.value > struct2.value);
	}
};


/**
@brief Provides an interface for the logic to load high scores from a file.
@author Dániel Eke
@credits Benjamin Ferenc Hajas
*/
class ScoreLoader
{
	/**
	@brief A class that loads scores from a file and puts them in a vector.
	@param filename The file to load the scores from.
	*/
public:
    ScoreLoader();
	/**
	@brief Creates a new Scoreloader.
	Creates a new Scoreloader.
	@param filename The file to load the scores from.
	*/
    ScoreLoader(std::string filename);
	/**
	@brief Returns top score.
	Returns top score.
	*/
    std::vector<Score> getTopScore();
	/**
	@brief Saves a new Score to the file.
	Saves a new Score to the file.
	*/
    void saveScore(std::string name, int score);
private:
    std::string scoreFileName = "defaultScores.txt";
    std::vector<Score> scores;
    void loadScores();
};

#endif //SCORE_LOADER_H