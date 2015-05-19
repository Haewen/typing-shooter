#ifndef POSITION_H
#define POSITION_H

#include <math.h>

/**
@brief Basic class to store a position
@author Benjamin Ferenc Hajas
*/
class Position
{
public:
	Position(){};
	/**
		@brief Creates a new Position.
		@param x,y	The x and y coordinates of the point.
	*/
	Position(int x, int y){ this->x=x; this->y = y; };
	/**
		@brief Copy constructor for the Position class.
	*/
	Position(const Position &position){ x= position.x; y = position.y; };
	/**
		@brief Returns the x position of the point.
		@returns the x position of the point.
	*/
	float getX(){ return x; };
	/**
	@brief Returns the y position of the point.
	@returns the y position of the point.
	*/
	float getY(){ return y; };
	/**
	@brief Changes the x coordinate of the point to a new one.
	@param x	The new x coordinate.
	*/
	void setX(float x) { this->x = x; };
	/**
	@brief Changes the y coordinate of the point to a new one.
	@param y	The new x coordinate.
	*/
	void setY(float y) { this->y = y; };
	/**
	@brief Changes the x and y coordinates of the point to a new one.
	@param x	The new x coordinate.
	@param y	The new y coordinate.
	*/
	void set(float x, float y) { setX(x); setY(y); };
	/** @brief Returns the distance to another position.
		@param position		Position to get the distance from.
	*/
	float distance(Position position)
	{ 	float disX = (position.x - x);
		float disY = (position.y - y);
		return sqrt(pow(disX,2)+pow(disY,2));
	};
protected:
	/**
	@brief The x coordinate of the point.
	*/
	float x;
	/**
	@brief The y coordinate of the point.
	*/
	float y;
};

#endif //POSITION_H