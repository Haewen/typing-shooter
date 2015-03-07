#include "Position.h"

Position::Position(){

}


Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position::Position(Position &position){
	position.x = this->x;
	position.y = this->y;
}

int Position::getX()
{
	return x;
}

int Position::getY()
{
	return y;
}

void Position::setX(int x)
{
	this->x = x;
}

void Position::setY(int y)
{
	this->y = y;
}

void Position::set(int x, int y){
	this->x = x;
	this->y = y;
}
