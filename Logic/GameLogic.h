/**
	Manages the whole game
	You can create a new gamemode by creating a subclass to this one.
	@author Benjamin Ferenc Hajas
*/

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "Enemy.h"
#include "Vocabulary.h"
#include <vector>
#include "Missile.h"
class GameLogic
{
public:
	GameLogic();

	/**
		Starts a new game.
		Automatically starts the first wawe!
	*/
	void newGame();

	//Starts the next wave.
	void nextWave();

	//Updates every enemy
	void update(float deltaTime); 

	/**
		Shoots target with a given character.
		If there is no target it will search for a new one.

		@return True if an enemy is hit.
	*/
	bool shoot(char c);

	int getScore(){ return score; };
	bool isGameOver(){ return gameOver; };
	Position getPlayerPosition(){ return playerPosition; };
	std::vector<Enemy>& getEnemies(){ return enemies;};
	std::vector <Missile>& getMissiles(){ return missiles; };
	int getWaveCount(){ return waveCount; };
	bool isWaveOver(){ return waveOver; };
	int getEnemyCount(){ return enemyCount; };
	Enemy& getTarget(){ return *target; };

protected:
	std::vector<Enemy> enemies;
	std::vector<Missile> missiles;
	int score,waveCount,enemyCount;
	bool gameOver;
	bool waveOver;
	int remainingEnemyCount;
	Position playerPosition;
	Enemy* target; //If there is no target it scans enemies for a suitable one
	Vocabulary* vocabulary;

	bool aim(char c); //Shoots at current target
	bool shootAt(char c);
	void createEnemies(); //Empties enemy list and creates new Enemies

	const int KILL_SCORE = 10; 
	const int BASE_ENEMY_COUNT = 5; 
	const int BONUS_ENEMY_PER_WAVE = 2; 
	const int SPAWN_RANGE = 25; 
	const int PLAYER_VERTICAL_POSITION = 95;
	const int PLAYER_HORIZONTAL_POSITION = 50;

	float easyChance, mediumChance, hardChance;
	float currentSpawnRange;

};

#endif //GAMELOGIC_H