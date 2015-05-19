/**
@brief Class to represent missile shot by player on succesful input
@authors Daniel Eke , Benjamin Ferenc Hajas
*/

#ifndef MISSILE_H
#define MISSILE_H

#include "Enemy.h"

class Missile
{
public:
	/**
		@brief Creates a new missile..
		@param playerPosition	The starting point of the missile.
		@param *target	A pointer to the missile's target.
		@param force The force of the missile.
	*/
	Missile(Position playerPosition, Enemy *target,float force = 4);
	/**
		@brief Updates the missile's position according to the deltaTime.
		@param deltaTime	The time between two frames.
	*/
	void update(float deltaTime);
	/**
		@brief Returns if the missile exploded or not.
		@returns true if the missile exploded.
		@returns false otherwise.
	*/
	bool isDead(){ return dead; };
	/**
		@brief Returns the position of the missile.
		@returns the position of the missile.
	*/
	Position getPosition() { return position; };
	
	/**
	@brief The speed of the missile.
	*/
	const int MOVEMENT_SPEED = 80;

protected:
	/**
	@brief	Target of the missile.
	*/
	Enemy *target;
	/**
	@brief	Position of the missile.
	*/
	Position position;
	/**
	@brief	Is the missile dead?
	*/
	bool dead;
	/**
	@brief	Force of the missile.
	*/
	float force;
};
#endif