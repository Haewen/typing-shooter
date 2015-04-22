/**
Missile shot by player on succesful input
@author D�niel Eke , Benjamin Ferenc Hajas
*/

#ifndef MISSILE_H
#define MISSILE_H

#include "Enemy.h"
class Missile
{
public:
	Missile(Position playerPosition, Enemy *target,float force = 4);
	void update(float deltaTime);
	bool isDead(){ return dead; };
	Position getPosition() { return position; };
	
protected:
	Enemy *target;
	const int MOVEMENT_SPEED = 80;
	Position position;
	bool dead;
	float force;
};
#endif