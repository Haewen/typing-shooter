#pragma once
#include <math.h>
class Position
{
public:
	Position(){};
	Position(int x, int y){ this->x=x; this->y = y; };
	Position(Position &position){ x= position.x; y = position.y; };
	float getX(){ return x; };
	float getY(){ return y; };
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	void set(float x, float y) { setX(x); setY(y); };
	//double distance(Position position){ return sqrt((double)((x - position.x) ^ 2) + (double)((y - position.y) ^ 2));};
	float distance(Position position)
	{ 	float disX = (position.x - x);
		float disY = (position.y - y);
		return sqrt(pow(disX,2)+pow(disY,2));
	};
protected:
	float x, y;
};

