/**
	Manages the whole game
	You can create a new gamemode by creating a subclass to this one.
	@author Benjamin Ferenc Hajas
*/

#include "GameLogic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream> // DEBUG

GameLogic::GameLogic(Position resolution)
{
	srand(time(NULL));
	this->resolution = resolution;
	PLAYER_VERTICAL_POSITION = resolution.getY() - 15;
	playerPosition = Position((resolution.getX() / 2), PLAYER_VERTICAL_POSITION);
	target = 0;
	vocabulary = new Vocabulary("Words/en");
}

void GameLogic::newGame()
{
	gameOver = false;
	score = 0;
	waveCount = 0;
	nextWave();
}

//Updates all enemies
void GameLogic::update(float deltaTime)
{
	if (remainingEnemyCount != 0)
	for (std::vector<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
	{
		if (!iterator->isDead()){
		iterator->update(deltaTime);
		if (iterator->getPosition().distance(playerPosition) < 5) gameOver = true;
		}
		}
	else waveOver = true;
}

//Looks for a target
bool GameLogic::aim(char c)
{
	for (std::vector<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
	{
		//e.g: input:'c'  Enemy text: "clever"
		if (iterator->getText()[0] == c && !iterator->isDead())
		{
			target = &(*iterator); 
			shootAt(c);
			return true;
		}
	}
	return false;
}

//Tries to shoot something
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

//Tries to shoot at a given enemy
bool GameLogic::shootAt(char c){
	//Did we hit the target?
	if (target->getText()[shotIndex] == c)
	{	//Is it dead?
		if (shotIndex+1 == (int)(target->getText().length()))
		{	
			shotIndex = 0;
			target->kill();
			score += KILL_SCORE;
			target = 0;
			remainingEnemyCount--;
		}
		shotIndex++;
		return true;
	}
	return false;
}

//Spawns enemies
void GameLogic::createEnemies()
{
	enemies.clear();
	enemyCount = BASE_ENEMY_COUNT + (waveCount - 1)  * BONUS_ENEMY_PER_WAVE;
	for (int i = 0; i < enemyCount; ++i)
	{
		std::string text = vocabulary->getRandomWord();
		std::cout << text << std::endl;
		Position p(rand() % ((int)resolution.getX()+1),-1* rand() % (SPAWN_RANGE));
		enemies.push_back(Enemy(text, p, playerPosition, 30));
		remainingEnemyCount++;
	}
}

void GameLogic::nextWave()
{
	waveOver = false;
	waveCount++;
	createEnemies();
}
