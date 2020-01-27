#pragma once
#include<list>
using namespace std;

#include<windows.h>

class SNAKE {

public:
	short INIT, dir;
	list<COORD> body;
	enum direction { UP = -1, DOWN = 1, LEFT = -10, RIGHT = 10 };

	SNAKE(const COORD &hCoord);
	bool isPositionAvailable(const COORD &pos);
	bool move(const COORD &hCoord, COORD &food);
	COORD placeFood(const COORD &hCoord);
};

