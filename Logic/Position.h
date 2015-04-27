/**
	Basic class to store a position
	@author Benjamin Ferenc Hajas
*/
#ifndef POSITION_H
#define POSITION_H

#include <math.h>
class Position
{
public:
	Position(){};
	Position(int x, int y){ this->x=x; this->y = y; };
	Position(const Position &position){ x= position.x; y = position.y; };
    
	float getX(){ return x; };
	float getY(){ return y; };
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	void set(float x, float y) { setX(x); setY(y); };
	/**Distance of 2 positions
		e.g. distance of (0,0) and (0,1) is 1.0f
	*/
	float distance(Position position)
	{ 	float disX = (position.x - x);
		float disY = (position.y - y);
		return sqrt(pow(disX,2)+pow(disY,2));
	};
protected:
	float x, y;
};

#endif //POSITION_H