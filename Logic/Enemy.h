#pragma once
#include "Position.h"
#include <string>
class Enemy
{
public:
	Enemy(std::string text, Position &position, Position &playerPosition,int movementSpeed);
	void update(float deltaTime);
	std::string getText();

private:
	Position position;
	std::string text;
	int movementSpeed;
	Position playerPosition;
};

