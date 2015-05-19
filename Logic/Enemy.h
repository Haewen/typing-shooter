#ifndef ENEMY_H
#define ENEMY_H

#include "Position.h"
#include <string>

/**
@brief Enemy's representation in logic.
@author Benjamin Ferenc Hajas
*/

class Enemy
{
public:
	/**
	@brief Creates a new Enemy.
	@param text	Text of the enemy.
	@param position	Position of the enemy.
	@param playerPosition	Position of the player.
	@param movementSpeed Movement speed of the enemy.
	@param acceleration Acceleration of the enemy.
	*/
	Enemy(std::string text, Position &position, Position &playerPosition,float movementSpeed,float acceleration);
	/**
	@brief Copy constructor for the Enemy class.
	*/
	Enemy(const Enemy &enemy);

	/**
		@Calculates movement based on the deltaTime parameter.
		@note Big deltaTimes can lead to inaccurate movement.
		@param deltaTime	The time between two frames.
	*/
	void update(float deltaTime);
	/**
	@brief Returns if the enemy is dead or not.
	@returns true if it is dead.
	@returns false otherwise.
	*/
	bool isDead(){ return dead; };
	/**
	@brief Returns if an enemy exploded or not.
	@returns true if a missile already hit the enemy.
	@returns false otherwise.
	*/
	bool isExploded(){ return exploded; };
	/**
	@brief Returns the text of the enemy.
	@returns a string of the enemy's text.
	*/
	std::string getText(){ return text; };
	/**
	@brief Returns the enemy's current position.
	@returns the enemy's current position.
	*/
	Position getPosition(){ return position; };
	/**
	@brief Returns if an enemy is on screen or not.
	@returns true if the enemy's y coordinate is >=0.
	@returns false otherwise.
	*/
	bool onScreen(){ return position.getY() >= 0; };
	/**
		@brief Returns true if this is a suitable target for the given character.
		@param c The character we try to shoot this enemy with.
	*/
	bool canShoot(char c);
	/**
		@brief Updates enemy on hit
	*/
	void hit(float force);
	/**
		@brief Shoots an enemy and removes its first letter.
		@note If enemy has no letters left it dies.
	*/
	void shoot();

protected:
	/**
	@brief Current position of the enemy.
	*/
	Position position;
	/**
	@brief Current text of the enemy.
	*/
	std::string text;
	/**
	@brief Enemy's maximum movement speed.
	*/
	float movementSpeed;
	/**
	@brief Enemy's current speed.
	*/
	float currentSpeed;
	/**
	@brief Enemy's acceleration.
	*/
	float acceleration;
	/**
	@brief Player's position.
	*/
	Position playerPosition;
	/**
	@brief Is enemy dead?
	*/
	bool dead;
	/**
	@brief Did enemy explode?
	*/
	bool exploded;
	/**
	@brief Enemy's current health.
	@note If the health is 0 the enemy dies.
	*/
	short health;

};

#endif // ENEMY_H