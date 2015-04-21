/**
Missile shot by player on succesful input
@author Dániel Eke , Benjamin Ferenc Hajas
*/

#include "Missile.h"

Missile::Missile(Position playerPosition, Enemy *target, float force)
{
	this->target = target;
	this->position = playerPosition;
	this->force = force;

	dead = false;
}

void Missile::update(float deltaTime)
{
	Position enemyPos = target->getPosition();
	if (position.distance(enemyPos) < 2)
	{
		target->hit(force);
		dead = true;
	}
	else
	{	
		float length = position.distance(enemyPos);
		float newPositionX = (enemyPos.getX() - position.getX()) / length * deltaTime * MOVEMENT_SPEED;
		float newPositionY = (enemyPos.getY() - position.getY()) / length * deltaTime * MOVEMENT_SPEED;
		position.set(position.getX() + newPositionX, position.getY() + newPositionY);
	}
}

