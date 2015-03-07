#include "GameLogic.h"


GameLogic::GameLogic()
{
}

void GameLogic::update(float deltaTime)
{
	for (std::list<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
	{
		iterator->update(deltaTime);
	}
}

bool GameLogic::aim(char c)
{
	for (std::list<Enemy>::iterator iterator = enemies.begin(), end = enemies.end(); iterator != end; ++iterator)
	{
		if (iterator->getText()[0] == c)
		{ 
			target = &(*iterator); 
			shootAt(target,c);
			return true;
		}
	}
	return false;
}

bool GameLogic::shoot(char c)
{
	if (target == 0){
		return aim(c);
	}
	else{
		return shootAt(target, c);
	}
}

bool GameLogic::shootAt(Enemy* enemy, char c){
	if (enemy->getText()[shotIndex] == c)
	{
		/*if (shotIndex == (int)(enemy->getText().length))
		{
			enemies.remove(*target);
			target = 0;
		}*/
		shotIndex++;
		return true;
	}
	return false;
}