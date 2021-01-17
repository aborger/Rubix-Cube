#include "Population.h"
#include "Cube.h"
#include "Output.h"
#include <Windows.h>
#include <iostream>

using namespace std;


// Constructor
Population::Population()
{
	for (int a = 0; a < 20; a++) {
		genes[a] = randMove();
	}
}

// Chooses random move
char Population::randMove() {
	char Moves[13] = {'L', 'l', 'R', 'r', 'U', 'u', 'D', 'd', 'F', 'f', 'B', 'b', ' '};
	int Random = rand() % 13;
	return Moves[Random];
}

//////// FFFFFFFFFFFFFFFIIIIIIIIIIIIIIIIIXXXXXXXXXXXXX!!!!!!!!!!!!
Cube Population::Fitness(Cube thisCube, int &fitness) {
	int fit = 0;
	// Performs moves
	for (int a = 0; a < 20; a++) {
		thisCube.pickMove(genes[a]);
	}
	//
	// Gives +1 fitness for each cube on correct side, 54 possible points in section --------------------------
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Front[r][c] == 'B')
				fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Back[r][c] == 'G')
				fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Left[r][c] == 'O')
				fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Right[r][c] == 'R')
				fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Up[r][c] == 'Y')
				fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Down[r][c] == 'W')
				fit++;
		}
	}

	// ----------------------------------------------------
	// Gives +1 fitness score if adjacent pieces are the same color, 72 possible points in section --------------------------------------

	// Front
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r != 3) {
				if (thisCube.Front[r][c] == thisCube.Front[r + 1][c])
					fit++;
			}
			if (c != 3) {
				if (thisCube.Front[r][c] == thisCube.Front[r][c + 1])
					fit++;
			}
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r != 3) {
				if (thisCube.Back[r][c] == thisCube.Back[r + 1][c])
					fit++;
			}
			if (c != 3) {
				if (thisCube.Back[r][c] == thisCube.Back[r][c + 1])
					fit++;
			}
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r != 3) {
				if (thisCube.Left[r][c] == thisCube.Left[r + 1][c])
					fit++;
			}
			if (c != 3) {
				if (thisCube.Left[r][c] == thisCube.Left[r][c + 1])
					fit++;
			}
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r != 3) {
				if (thisCube.Right[r][c] == thisCube.Right[r + 1][c])
					fit++;
			}
			if (c != 3) {
				if (thisCube.Right[r][c] == thisCube.Right[r][c + 1])
					fit++;
			}
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r != 3) {
				if (thisCube.Up[r][c] == thisCube.Up[r + 1][c])
					fit++;
			}
			if (c != 3) {
				if (thisCube.Up[r][c] == thisCube.Up[r][c + 1])
					fit++;
			}
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r != 3) {
				if (thisCube.Down[r][c] == thisCube.Down[r + 1][c])
					fit++;
			}
			if (c != 3) {
				if (thisCube.Down[r][c] == thisCube.Down[r][c + 1])
					fit++;
			}
		}
	}
	// --------------------------------------------------------------------------------------------

	// Gives +1 fitness for each row done, 18 possible points in section ------------------------------------------------------------
	for (int r = 0; r < 3; r++) {
		if (thisCube.Front[r][0] == thisCube.Front[r][1] && thisCube.Front[r][0] == thisCube.Front[r][2])
			fit++;
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Back[r][0] == thisCube.Back[r][1] && thisCube.Back[r][0] == thisCube.Back[r][2])
			fit++;
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Right[r][0] == thisCube.Right[r][1] && thisCube.Right[r][0] == thisCube.Right[r][2])
			fit++;
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Left[r][0] == thisCube.Left[r][1] && thisCube.Left[r][0] == thisCube.Left[r][2])
			fit++;
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Up[r][0] == thisCube.Up[r][1] && thisCube.Up[r][0] == thisCube.Up[r][2])
			fit++;
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Down[r][0] == thisCube.Down[r][1] && thisCube.Down[r][0] == thisCube.Down[r][2])
			fit++;
	}

	// Gives +1 for each side done, 6 possible points for a total of 150
	int same = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Front[r][c] == thisCube.Front[1][1]) {
				same++;
			}
		}
	}
	if (same == 9) {
		fit++;
	}
	same = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Back[r][c] == thisCube.Back[1][1]) {
				same++;
			}
		}
	}
	if (same == 9) {
		fit++;
	}
	same = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Left[r][c] == thisCube.Left[1][1]) {
				same++;
			}
		}
	}
	if (same == 9) {
		fit++;
	}
	same = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Right[r][c] == thisCube.Right[1][1]) {
				same++;
			}
		}
	}
	if (same == 9) {
		fit++;
	}
	same = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Up[r][c] == thisCube.Up[1][1]) {
				same++;
			}
		}
	}
	if (same == 9) {
		fit++;
	}
	same = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Down[r][c] == thisCube.Down[1][1]) {
				same++;
			}
		}
	}
	if (same == 9) {
		fit++;
	}
	fit = fit / 1.5;
	fitness = fit;
	return thisCube;
}





//Population::~Population()
//{
//}
