#pragma once
#include "Cube.h"
class InputNode
{
private:
	int row;
	int col;
	char face; //Face must be caps
public:
	InputNode();
	InputNode(char f, int r, int c);
	double getValue(Cube thisCube);
	~InputNode();
};

