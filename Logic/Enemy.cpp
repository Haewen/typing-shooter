/**
	Enemy's representation in Logic.
	@author Benjamin Ferenc Hajas
*/

#include "Enemy.h"

Enemy::Enemy(std::string text,Position &position,Position &playerPosition,float movementSpeed,float acceleration)
{
	dead = false;
	exploded = false;
	this->text = text;
	this->position = position;
	this->movementSpeed = movementSpeed;
	this->playerPosition = playerPosition;
	this->currentSpeed = 0;
	this->acceleration = acceleration;
	this->health = text.size();
}

Enemy::Enemy(const Enemy &enemy)
{
	dead = enemy.dead;
	exploded = enemy.exploded;
	text = enemy.text;
	position = enemy.position;
	movementSpeed = enemy.movementSpeed;
	playerPosition = enemy.playerPosition;
	acceleration = enemy.acceleration;
	currentSpeed = enemy.currentSpeed;
	health = enemy.health;
}

void Enemy::update(float deltaTime)
{
	if (currentSpeed < movementSpeed)
	{
		currentSpeed += (acceleration * deltaTime);
	}
	float length = position.distance(playerPosition);
	float newPositionX = (playerPosition.getX()- position.getX()) / length * deltaTime * currentSpeed;
	float newPositionY = (playerPosition.getY() - position.getY()) / length * deltaTime * currentSpeed;
	position.set(position.getX() + newPositionX, position.getY() + newPositionY);

}

bool Enemy::canShoot(char c)
{
	if (text[0] == c && !dead && onScreen()) return true;
	return false;
}

void Enemy::hit(float force)
{
		currentSpeed -= force;
		health--;
		if (health == 0)
		{
			exploded = true;
		}
}

void Enemy::shoot()
{
	text.erase(0, 1);
	if (text.length() == 0) dead = true;
}