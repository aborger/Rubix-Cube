/* Two classes:
	Population:
		Each object is a population filled with 20 moves, hopefully those moves will solve the cube when the algorithm is complete
	Cube:
		The objects contain the progress of the cube after 20 moves, for each individual set of moves*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "Population.h"


using namespace std;

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::											Function Prototypes										::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
Cube scrambleCube(Cube thisCube); // Picks 25 random moves to perform on a completed cube
void outputCube(Cube thisCube); // Displays a cube to the screen

int call(Population pop[], Cube Cube); // Shows the user the progress

void selection(Population pop[]); // Normalizes fitness numbers
int choose(Population pop[]); // Picks a random member to reproduce, members with higher fitness are more likely to be selected
void newPopulation(Population pop[], Population newPop[]); // Creates a new population to test
void cross(Population pop[], Population newPop[], int choice1, int choice2, int &iterations); // Crosses genes to produce two new members
void mutate(Population pop[]); // Randomly mutates genes


#include <stdio.h>
#include <time.h>

//void wait(int seconds);


 
const int popNum = 100; // Number of individuals in population, MUST BE EVEN!!!
int mutation = 7; // The percantage chance of mutating
int generation = 0;



/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::												Main												::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

int main() {
	srand(time(NULL));

	int finish = 0;
	Cube newCube;
	newCube = scrambleCube(newCube);
	outputCube(newCube);
	system("PAUSE");

	Population pop[popNum]; // Generates a population with popNum individuals
	
	call(pop, newCube);
	Population newPop[popNum];
	while (finish != 100) {
		newPopulation(pop, newPop);
		for (int a = 0; a < popNum; a++) {
			pop[a] = newPop[a];
		}
		finish = call(pop, newCube);
		//system("PAUSE");
	}
	system("CLS");
	cout << "WE DID IT!!";
	system("PAUSE");
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::											Functions												::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*void solvedCube(Cube thisCube) {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			thisCube.Front[r][c] = 'B';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			thisCube.Back[r][c] = 'G';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			thisCube.Left[r][c] = 'O';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			thisCube.Right[r][c] = 'R';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			thisCube.Up[r][c] = 'Y';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			thisCube.Down[r][c] = 'W';
		}
	}
}*/
Cube scrambleCube(Cube thisCube) {
	srand(time(NULL));
	for (int a = 0; a < 25; a++) {
		char Moves[13] = { 'L', 'l', 'R', 'r', 'U', 'u', 'D', 'd', 'F', 'f', 'B', 'b', ' ' };
		int Random = rand() % 13;
		thisCube.pickMove(Moves[Random]);
	}
	return thisCube;
}


int call(Population pop[], Cube thisCube) {
	int best = 0;
	int bestfit = 0;
	Cube tempCube;
	Cube bestCube;
	int fit = 0;
	system("CLS");
	for (int a = 0; a < popNum; a++) {
		tempCube = pop[a].Fitness(thisCube, fit);
		pop[a].fitness = fit;
		if (pop[a].fitness > bestfit) {
			best = a;
			bestfit = pop[a].fitness;
			bestCube = tempCube;
		}
	}
	cout << "Generation: " << generation << endl;
	generation++;
	cout << "Best Member: " << best << endl;
	for (int a = 0; a < 20; a++) {
		cout << " " << pop[best].genes[a] << ",";
	}
	selection(pop);
	cout << endl << "With a score of: " << pop[best].fitness << endl;
	outputCube(bestCube);
	//wait(1);
	return bestfit;
}

//------------------------------------------- Genetics ---------------------------------------------------------------||
// Giving members their probability of being picked (based on a percentage out of 100%)
void selection(Population pop[]) {
	int sum = 0;
	int prevProb = 0;
	for (int a = 0; a < popNum; a++) {
		sum += pop[a].fitness;
	}
	if ((sum % 2) != 0) {
		sum = sum - 1;
	}
	for (int a = 0; a < popNum; a++) {
		pop[a].fitness = prevProb + (pop[a].fitness / (sum / 100));
		prevProb = pop[a].fitness;
	}
}

// Returns index of member to repopulate
int choose(Population pop[]) {
	int choice = rand() % 99;
	for (int a = 0; a < popNum; a++) {
		if (choice < pop[a].fitness) {
			return a;
		}
	}
}

void newPopulation(Population pop[], Population newPop[]) {
	int choice1 = 0;
	int choice2 = 0;

	for (int iterations = 0; iterations < popNum; iterations++) {
		choice1 = choose(pop);
		choice2 = choose(pop);
		cross(pop, newPop, choice1, choice2, iterations);
		iterations++;
	}
	mutate(newPop);
}
/////////////////////////////// Fix!!!!!!!!!!!!!!!!!!!!1
void cross(Population pop[], Population newPop[], int choice1, int choice2, int &iterations) {
	int randNum = rand() % 20;
	for (int a = 0; a < randNum; a++) {
		newPop[iterations].genes[a] = pop[choice1].genes[a];
		newPop[iterations + 1].genes[a] = pop[choice2].genes[a];
	}
	for (int a = randNum; a < 20; a++) {
		newPop[iterations].genes[a] = pop[choice2].genes[a];
		newPop[iterations + 1].genes[a] = pop[choice1].genes[a];
	}
}

void mutate(Population pop[]) {
	for (int member = 0; member < popNum; member++) {
		if (rand() % 100 < mutation) {
			pop[member].genes[rand() % 20] = pop[member].randMove(); // Picks a random move to put into the gene
		}
	}
}






/*void wait(int seconds)
{
	clock_t endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
}*/