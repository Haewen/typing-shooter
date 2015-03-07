#pragma once
#include "Position.h"
#include <string>
class Enemy
{
public:
	Enemy(std::string text, Position &position, Position &playerPosition,int movementSpeed);
	Enemy(const Enemy &enemy);
	void update(float deltaTime); //Called every frame
	std::string getText(){ return text; }; 
	void kill(){ dead; }; 
	int getDifficulty(){ return difficulty; };
	bool isDead(){ return dead; };
	Position getPosition(){ return position; };

protected:
	Position position;
	std::string text;
	int movementSpeed,difficulty;
	Position playerPosition;
	bool dead;
	void setDifficulty();
};

