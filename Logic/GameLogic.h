#pragma once
#include "Enemy.h"
#include <list>
class GameLogic
{
public:
	GameLogic();
	void update(float deltaTime);
	int getScore();
	void newGame();
	bool shoot(char c);
private:
	std::list<Enemy> enemies;
	int score,waveCount,shotIndex;
	bool gameOver;
	Enemy* target;
	bool aim(char c);
	bool shootAt(Enemy* target, char c);
};

