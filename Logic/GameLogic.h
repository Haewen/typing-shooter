#pragma once
#include "Enemy.h"
#include <list>
class GameLogic
{
public:
	GameLogic(Position resolution);
	void newGame();
	bool shoot(char c);
	void update(float deltaTime); //Called every frame
	bool changeResolution(Position resolution){ this->resolution = resolution; };
	int getScore(){ return score; };
	bool isGameOver(){ return gameOver; };
	Position getPlayerPosition(){ return playerPosition; };
	std::list<Enemy> getEnemies(){ return enemies;};
	void nextWave();

protected:
	std::list<Enemy> enemies;
	int score,waveCount,shotIndex,enemyCount;
	bool gameOver;
	bool waveOver;
	int remainingEnemyCount;
	Position resolution;
	Position playerPosition;
	Enemy* target; //If there is no target it scans enemies for a suitable one

	bool aim(char c); //Shoots at current target
	bool shootAt(char c);
	void createEnemies(); //Empties enemy list and creates new Enemies

	const int KILL_SCORE = 10; 
	const int BASE_ENEMY_COUNT = 5; 
	const int BONUS_ENEMY_PER_WAVE = 2; 
	const int SPAWN_RANGE = 10; 
	const int PLAYER_VERTICAL_POSITION = 10;

};

