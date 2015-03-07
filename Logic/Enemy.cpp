#include "Enemy.h"


Enemy::Enemy(std::string text,Position &position,Position &playerPosition,int movementSpeed)
{
	this->text = text;
	this->position = position;
	this->movementSpeed = movementSpeed;
	this->playerPosition = playerPosition;
}

void Enemy::update(float deltaTime)
{
	float length = sqrt(playerPosition.getX()^2 + playerPosition.getY()^2);
	int newPositionX = position.getX() / length * deltaTime * movementSpeed;
	int newPositionY = position.getY() / length * deltaTime * movementSpeed;
	position.set(position.getX() + newPositionX, position.getY() + newPositionY);
}

std::string Enemy::getText()
{
	return text;
}