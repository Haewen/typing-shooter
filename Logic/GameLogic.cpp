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

GameLogic::GameLogic()
{
	srand(time(NULL));
	playerPosition = Position(PLAYER_HORIZONTAL_POSITION, PLAYER_VERTICAL_POSITION);
	target = 0;
	vocabulary = new Vocabulary("Words/en");
	currentSpawnRange = SPAWN_RANGE;
}

void GameLogic::newGame()
{
	gameOver = false;
	score = 0;
	waveCount = 0;
	nextWave();
	easyChance = 97;
	mediumChance = 2;
	hardChance = 1;
	currentSpawnRange = SPAWN_RANGE;
}

//Updates all enemies
void GameLogic::update(float deltaTime)
{
	if (remainingEnemyCount != 0)
	{
		for (std::vector<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
		{
			if (!iterator->isExploded())
			{
				iterator->update(deltaTime);
				if (iterator->getPosition().distance(playerPosition) < 1) gameOver = true;
			}
		}

		for (std::vector<Missile>::iterator iterator = missiles.begin(), end = missiles.end(); iterator != end; ++iterator)
		{
			if (!iterator->isDead())
			{
				iterator->update(deltaTime);
			}
		}
		
	}
	else waveOver = true;
}

//Looks for a target
bool GameLogic::aim(char c)
{
	std::vector<std::vector<Enemy>::iterator> possibleTargets;
	for (std::vector<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
	{
		//e.g: input:'c'  Enemy text: "clever"
		if (iterator->canShoot(c))
		{	
			possibleTargets.push_back(iterator);
		}
	}
	//Choosing best target
	if (possibleTargets.size() > 0)
	{
		int choice;
		if (possibleTargets.size() == 1)
		{
			choice = 0;
		}
		else
		{
			int minDistance = 100; //Screen size is 100
			for (int i = 0; i < possibleTargets.size(); i++)
			{
				int d = possibleTargets[i]->getPosition().distance(playerPosition);
				if (d < minDistance)
				{
					minDistance = d;
					choice = i;
				}
			}
		}
		target = &(*possibleTargets[choice]);
		shootAt(c);
		return true;
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
	if (target->canShoot(c))
	{	//Is it dead?
			//target->hit(5);
			missiles.push_back(Missile(playerPosition,target));
			target->shoot();
			if (target->isDead())
			{
				score += KILL_SCORE;
				target = 0;
				remainingEnemyCount--;
			}
			return true;
	}
	return false;
}

//Spawns enemies
void GameLogic::createEnemies()
{
	enemies.clear();
	enemyCount = BASE_ENEMY_COUNT + (waveCount - 1)  * BONUS_ENEMY_PER_WAVE ;
	for (int i = 0; i < enemyCount; ++i)
	{
		int enemyDiff = rand() % 100;
		std::string text;

		if (enemyDiff < hardChance)
		{
			text = vocabulary->getRandomWord(Difficulty::Hard);
		}else
		if (enemyDiff < mediumChance + hardChance)
		{
			text = vocabulary->getRandomWord(Difficulty::Medium);
		}
		else
		text = vocabulary->getRandomWord(Difficulty::Easy);

		Position p(rand() % 100,-1*( 5 + i * currentSpawnRange));
		enemies.push_back(Enemy(text, p, playerPosition, 10,20));
		remainingEnemyCount++;
	}

	int easy_t = easyChance;
	easyChance *= 0.9f;
	mediumChance += 100 / (easy_t - easyChance) * 0.7f;
	hardChance = 100 - mediumChance - easyChance;

	currentSpawnRange *= 0.90f;

}

void GameLogic::nextWave()
{
	missiles.clear();
	waveOver = false;
	waveCount++;
	createEnemies();
}
