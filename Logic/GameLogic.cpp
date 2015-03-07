#include "GameLogic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GameLogic::GameLogic(Position resolution)
{
	srand(time(NULL));
	this->resolution = resolution;
	playerPosition = Position((resolution.getX() / 2), PLAYER_VERTICAL_POSITION);
}

void GameLogic::newGame()
{
	gameOver = false;
	score = 0;
	waveCount = 0;
	nextWave();
}

void GameLogic::update(float deltaTime)
{
	if (remainingEnemyCount != 0)
		for (std::vector<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
		{
			iterator->update(deltaTime);
			if (iterator->getPosition().distance(playerPosition) < 5) gameOver = true;
		}
	else waveOver = true;
}


bool GameLogic::aim(char c)
{
	for (std::vector<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
	{
		//e.g: input:'c'  Enemy text: "clever"
		if (iterator->getText()[0] == c)
		{	
			target = &(*iterator); 
			shootAt(c);
			return true;
		}
	}
	return false;
}

bool GameLogic::shoot(char c)
{
	//Do we have a target?
	if (target == 0){
		//Look for a target
		return aim(c);
	}
	else{
		//Try to shoot at target
		return shootAt(c);
	}
}

bool GameLogic::shootAt(char c){
	//Did we hit the target?
	if (target->getText()[shotIndex] == c)
	{	//Is it dead?
		if (shotIndex == (int)(target->getText().length()))
		{	
			shotIndex = 0;
			target->kill();
			score += target->getDifficulty() * KILL_SCORE;
			target = 0;
			remainingEnemyCount--;
		}
		shotIndex++;
		return true;
	}
	return false;
}

void GameLogic::createEnemies()
{
	enemies.empty();
	enemyCount = BASE_ENEMY_COUNT + (waveCount - 1)  * BONUS_ENEMY_PER_WAVE;
	for (int i = 0; i < enemyCount; ++i)
	{
		std::string text = "Placeholder";
		Position p(rand() % (resolution.getX()+1), rand() % (-SPAWN_RANGE));
		enemies.push_back(Enemy(text, p, playerPosition, 30));
		remainingEnemyCount++;
	}
}

void GameLogic::nextWave()
{
	waveCount++;
	createEnemies();
}
