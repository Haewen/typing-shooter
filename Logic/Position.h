#pragma once
class Position
{
public:
	Position();
	Position(int x, int y);
	Position(Position &position);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void set(int x, int y);

private:
	int x, y;
};

