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
	Enemy(std::string text, Position &position, Position &playerPosition,float movementSpeed,float acceleration);
	Enemy(const Enemy &enemy);

	/**
		Calculates movement based on the deltaTime parameter.
		Big deltaTimes can lead to inaccurate movement.
	*/
	void update(float deltaTime);
	bool isDead(){ return dead; };
	bool isExploded(){ return exploded; };
	std::string getText(){ return text; }; 
	Position getPosition(){ return position; };
	bool onScreen(){ return position.getY() >= 0; };
	//Returns true if this is a suitable target
	bool canShoot(char c);
	//Updates enemy on hit
	void hit(float force);
	void shoot();

protected:
	Position position;
	std::string text;
	//Maximum movement speed!
	float movementSpeed;
	float currentSpeed;
	float acceleration;
	Position playerPosition;
	bool dead;
	bool exploded;
	short health;

};

#endif // ENEMY_H