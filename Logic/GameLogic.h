#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Enemy.h"
#include "Vocabulary.h"
#include <vector>
#include "Missile.h"

/**
@brief Manages the whole game
@note You can create a new gamemode by creating a subclass to this one.
@author Benjamin Ferenc Hajas
*/
class GameLogic
{
public:
	/**
	@brief Creates a new GameLogic.
	*/
	GameLogic();
	/**
	@brief Copy constructor for the GameLogic.
	*/
    GameLogic( const GameLogic &obj);

	/**
		@brief Starts a new game.
		@note Automatically starts the first wawe!
	*/
	void newGame();

	/**
		@brief Starts the next wave.
	*/
	void nextWave();

	/**
		@brief Updates every enemy
	*/
	void update(float deltaTime); 

	/**
		@brief Shoots target with a given character.
		If there is no target it will search for a new one.

		@returns True if an enemy is hit.
	*/
	bool shoot(char c);

	/**
		@brief Returns the current score.
		@returns the current score.
	*/
	int getScore(){ return score; };
	/**
		@brief Returns if game is over or not.
		@returns true if game is over.
		@returns false otherwise.
	*/
	bool isGameOver(){ return gameOver; };
	/**
		@brief Returns the player's position.
		@returns the player's position.
	*/
	Position getPlayerPosition(){ return playerPosition; };
	/**
		@brief Returns a list of the current enemies.
		@returns a reference of the list of the current enemies.
	*/
	std::vector<Enemy>& getEnemies(){ return enemies;};
	/**
		@brief Returns a list of the current missiles.
		@returns a reference of the list of the current missiles.
	*/
	std::vector <Missile>& getMissiles(){ return missiles; };
	/**
		@brief Returns the current wave's index.
		@returns the current wave's index.
	*/
	int getWaveCount(){ return waveCount; };
	/**
		@brief Returns if the wave is over or not.
		@returns true if wave is over.
		@returns false otherwise.
	*/
	bool isWaveOver(){ return waveOver; };
	/**
		@brief Returns the count of the current enemies.
		@returns the count of the current enemies.
	*/
	int getEnemyCount(){ return enemyCount; };
		/**
		@brief Returns the current target.
		@returns null if there isn't one.
		*/
	Enemy& getTarget(){ return *target; };

protected:
	/**
	@brief List of the current enemies.
	*/
	std::vector<Enemy> enemies;
	/**
	@brief List of the currently active missiles.
	*/
	std::vector<Missile> missiles;
	/**
	@brief Current score.
	*/
	int score; 
	/**
	@brief Current waveCount.
	*/
	int waveCount;
	/**
	@brief Current enemy count.
	*/
	int enemyCount;
	/**
	@brief Is game over?
	*/
	bool gameOver;
	/**
	@brief Is wave over?.
	*/
	bool waveOver;
	/**
	@brief Remaining enemies alive.
	*/
	int remainingEnemyCount;
	/**
	@brief Position of the player.
	*/
	Position playerPosition;
	/**
	@brief Current target.
	*/
	Enemy* target; 
	/**
	@brief Vocabulary of the game.
	*/
	Vocabulary* vocabulary;

	/**
		@brief Looks for a target.
		@param c	The character the suitable target's text starts with.
	*/
	bool aim(char c); 
	/**
	@brief Shoots at current target.
	@param c	A character from the user's input.
	*/
	bool shootAt(char c);
	/**
	@brief Empties enemy list and fills it with new ones.
	*/
	void createEnemies();

	/**
		@brief Base score for killing a target.
	*/
	const int KILL_SCORE = 10; 
	/**
	@brief Base enemy count for a wave.
	*/
	const int BASE_ENEMY_COUNT = 5; 
	/**
	@brief Base bonus enemy count for a wave.
	*/
	const int BONUS_ENEMY_PER_WAVE = 2; 
	/**
	@brief Base spawn range for enemies.
	*/
	const int SPAWN_RANGE = 15; 
	/**
	@brief Player's relative vertical position.
	*/
	const int PLAYER_VERTICAL_POSITION = 95;
	/**
	@brief Player's relative horizontal position.
	*/
	const int PLAYER_HORIZONTAL_POSITION = 50;

	/**
	@brief Chance to spawn an easy enemy.
	*/
	float easyChance;
	/**
	@brief Chance to spawn a medium enemy.
	*/
	float mediumChance; 
	/**
	@brief Chance to spawn a hard enemy.
	*/
	float hardChance;
	/**
	@brief Current spawn range.
	*/
	float currentSpawnRange;

};

#endif //GAMELOGIC_H