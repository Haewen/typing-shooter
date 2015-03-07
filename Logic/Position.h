#pragma once
#include <math.h>
class Position
{
public:
	Position(){};
	Position(int x, int y){ this->x=x; this->y = y; };
	Position(Position &position){ x= position.x; y = position.y; };
	int getX(){ return x; };
	int getY(){ return y; };
	void setX(int x) { this->x = x; };
	void setY(int y) { this->y = y; };
	void set(int x, int y) { setX(x); setY(y); };
	//double distance(Position position){ return sqrt((double)((x - position.x) ^ 2) + (double)((y - position.y) ^ 2));};
	double distance(Position position)
	{ 	double disX = (position.x - x);
		double disY = (position.y - y);
		return sqrt(pow(disX,2)+pow(disY,2));
	};
protected:
	int x, y;
};

