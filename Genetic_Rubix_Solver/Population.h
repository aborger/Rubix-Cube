#pragma once
#include "Cube.h"

class Population
{
public:
	int fitness;
	char genes[20];

	Population();
	char randMove();
	Cube Fitness(Cube thisCube, int &fit);
	//~Population();
};

