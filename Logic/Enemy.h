/**
	Enemy's representation in logic.
	@author Benjamin Ferenc Hajas
*/

#ifndef ENEMY_H
#define ENEMY_H

#include "Position.h"
#include <string>
class Enemy
{
public:
	Enemy(std::string text, Position &position, Position &playerPosition,int movementSpeed);
	Enemy(const Enemy &enemy);

	/**
		Calculates movement based on the deltaTime parameter.
		Big deltaTimes can lead to inaccurate movement.
	*/
	void update(float deltaTime);
	bool isDead(){ return dead; };
	std::string getText(){ return text; }; 
	Position getPosition(){ return position; };
	bool onScreen(){ return position.getY() >= 0; };
	bool canShoot(char c);
	void hit();

protected:
	Position position;
	std::string text;
	int movementSpeed;
	Position playerPosition;
	bool dead;
};

#endif // ENEMY_H