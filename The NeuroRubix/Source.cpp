#include "Node.h"
#include "Genome.h"
#include "Cube.h"
#include "List.h"
#include <iostream>
#include <math.h>
#include <time.h>


using namespace std;
/* 
Current methods of genetic algorithm
Selection: Fitness propogation
Reproduction: The amount below selectPercent is kept as an elite, the rest are selected in fitness propogation
Mutation: Bias and Weight are being slightly changed using rand num and sigmoid function




Things to make better:      in order of easy to hard
- Initial Population
	Change Variable
- Make Better Fitness Function
- Add Speciation
- NN chooses best move percent not random chance based on percentage
	In Genome.getMove()
- Doesn't cross produce
	fix mutation function [how nodes and connections are destroyed]
- Doesn't look ahead
	Include Move '/' to stop
	Change all 13's output nodes [Genome::getMove(), Main::Mutate()]
*/

// Struct to hold the population
struct Population {
	Genome networks;
	double fitness;
	double probFit;
	bool selected;
};

// Function Prototypes
void getFitness(List<Population> &pop, Cube mainCube, double &bestFit, Cube &bestCube, int &bestPop, List<char> &bestMove, int numMoves);
int fitness(List<char> moves, int numMoves, Cube &thisCube);
Population selection(List<Population> pop, int initialPop);
List <Population> reproduce(List<Population> pop, int initialPop, double selectPercent);
void mutate(List<Population> &pop, int mutatePercent, int trainVnew);




int main() {
	double bestFit = 0;
	Cube bestCube;
	int bestPop;
	List<char> bestMove;


	// ------------------ Values to Change -----------------
	int initialPop = 100; // The initial population, make even
	double selectPercent = .1; // The percentage the selection function will keep
	int mutatePercent = 10; // The percentage an item will be mutated
	int trainVnew = 90; // Used in mutation, should be more likely to train than make new neural networks (75 value means 3/4 of the time will train)
	int numMoves = 1;

	// ----------------------- Setup ------------------------
	List<Population> pop;
	Cube mainCube;
	srand(time(NULL));
	for (int a = 0; a < initialPop; a++) {
		Population *temp = NULL;
		temp = new Population;
		temp->networks.randFill();
		pop.newNodeTail(*temp);
	}

	//mainCube.scrambleCube();
	mainCube.L();
	cout << "Starting Cube: " << endl;
	mainCube.outputCube();
	system("PAUSE");
	// ------------------ Functionality ----------------------*/
	bool stop = false;
	int generations = 0;
	getFitness(pop, mainCube, bestFit, bestCube, bestPop, bestMove, numMoves);
	pop = reproduce(pop, initialPop, selectPercent);
	mutate(pop, mutatePercent, trainVnew);
	while (bestFit < 100) {
		system("CLS");
		cout << "Generation: " << generations << endl;
		getFitness(pop, mainCube, bestFit, bestCube, bestPop, bestMove, numMoves);
		pop = reproduce(pop, initialPop, selectPercent);
		mutate(pop, mutatePercent, trainVnew);


		generations++;
		cout << "Best Individual: " << bestPop << endl;
		cout << "Fitness: " << bestFit << endl;
		/*for (int a = 0; a < pop.getListSize(); a++) {
			cout << "Pop: " << a << endl;
			pop.getAt(a).networks.outputGenes();
		}
		
		/*pop.getAt(1).networks.outputGenes();
		pop.getAt(2).networks.outputGenes();
		pop.getAt(3).networks.outputGenes();
		pop.getAt(4).networks.outputGenes();*/
		//system("PAUSE");
	}
		pop.getAt(bestPop).networks.outputGenes();
		cout << "Moves: ";
		for (int a = 0; a < numMoves; a++) {
			cout << bestMove.getAt(a);
			cout << ", ";
		}
		cout << endl;
		bestCube.outputCube();
		system("PAUSE");
}

void getFitness(List<Population> &pop, Cube mainCube, double &bestFit, Cube &bestCube, int &bestPop, List<char> &bestMove, int numMoves) {
	bestFit = -1;
	double fitSum = 0;
	Cube tempCube;
	for (int a = 0; a < pop.getListSize(); a++) {
		// gets the moves
		List <char> Moves;
		tempCube = mainCube;
		pop.getAt(a).networks.getMove(Moves, numMoves);
		Population temporary = pop.getAt(a);

		temporary.fitness = fitness(Moves, numMoves, tempCube);
		temporary.probFit = temporary.fitness;
		pop.setAt(a, temporary);
		// adds fitness to sum
		fitSum += pop.getAt(a).fitness;

		// finds best fitness
		if (pop.getAt(a).fitness > bestFit) {
			bestFit = pop.getAt(a).fitness;
			bestCube = tempCube;
			bestPop = a;
			bestMove = Moves;
		}
	}
	// Replaces fitness numbers with probability numbers
	double previousProb = 0;
	for (int a = 0; a < pop.getListSize(); a++) {
		Population temp = pop.getAt(a);
		temp.probFit = previousProb + (pop.getAt(a).probFit / fitSum);
		pop.setAt(a, temp);
		previousProb = pop.getAt(a).probFit;
	}
}

int fitness(List<char> moves, int numMoves, Cube &thisCube) {

	int fit = 0;

	// Used to check if each task is complete
	int check = 0;
	char move;
	// Performs moves
	for (int a = 0; a < numMoves; a++) {
		move = moves.getAt(a);
		thisCube.pickMove(move);
	}
	// Fitness scores first number is how much that combo is worth, second number is the number of combos, max fitness is 100, a score of 100 means it is completed

	// 10 * 1 completed
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Front[r][c] == thisCube.Front[1][1])
				check++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Back[r][c] == thisCube.Back[1][1])
				check++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Left[r][c] == thisCube.Left[1][1])
				check++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Right[r][c] == thisCube.Right[1][1])
				check++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Up[r][c] == thisCube.Up[1][1])
				check++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Down[r][c] == thisCube.Down[1][1])
				check++;
		}
	}

	if (check == 54) {
		fit = 100; // if the cube is complete return highest score possible and exit
		return fit;
	}
	// 4 * 6 sides
	check = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Front[r][c] == thisCube.Front[1][1])
				check++;
		}
	}
	if (check == 6) {
		fit += 4;
	}
	check = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Back[r][c] == thisCube.Back[1][1])
				check++;
		}
	}
	if (check == 6) {
		fit += 4;
	}
	check = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Left[r][c] == thisCube.Left[1][1])
				check++;
		}
	}
	if (check == 6) {
		fit += 4;
	}
	check = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Right[r][c] == thisCube.Right[1][1])
				check++;
		}
	}
	if (check == 6) {
		fit += 4;
	}
	check = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Up[r][c] == thisCube.Up[1][1])
				check++;
		}
	}
	if (check == 6) {
		fit += 4;
	}
	check = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (thisCube.Down[r][c] == thisCube.Down[1][1])
				check++;
		}
	}
	if (check == 6) {
		fit += 4;
	}
	// 3 * 3 full cube horizontal rows
	for (int r = 0; r < 3; r++) {
		check = 0;
		for (int c = 0; c < 3; c++) {
			if (thisCube.Front[r][c] == thisCube.Front[1][1]) {
				check++;
			}
			if (thisCube.Right[r][c] == thisCube.Right[1][1]) {
				check++;
			}
			if (thisCube.Back[r][c] == thisCube.Back[1][1]) {
				check++;
			}
			if (thisCube.Left[r][c] == thisCube.Left[1][1]) {
				check++;
			}
		}
		if (check == 12) {
			fit += 3;
		}
	}
	// 3 * 3 full cube vertical rows
	for (int c = 0; c < 3; c++) {
		check = 0;
		for (int r = 0; r < 3; r++) {
			if (thisCube.Front[r][c] == thisCube.Front[1][1]) {
				check++;
			}
			if (thisCube.Up[r][c] == thisCube.Up[1][1]) {
				check++;
			}
			if (thisCube.Back[r][c] == thisCube.Back[1][1]) {
				check++;
			}
			if (thisCube.Down[r][c] == thisCube.Down[1][1]) {
				check++;
			}
		}
		if (check == 12) {
			fit += 3;
		}
	}
	// 2 * 6 crosses
	check = 0;
	if (thisCube.Front[0][1] == thisCube.Front[1][1]) {
		check++;
	}
	if (thisCube.Front[1][0] == thisCube.Front[1][1]) {
		check++;
	}
	if (thisCube.Front[2][1] == thisCube.Front[1][1]) {
		check++;
	}
	if (thisCube.Front[1][2] == thisCube.Front[1][1]) {
		check++;
	}
	if (check == 4) {
		fit += 2;
	}
	check = 0;
	if (thisCube.Back[0][1] == thisCube.Back[1][1]) {
		check++;
	}
	if (thisCube.Back[1][0] == thisCube.Back[1][1]) {
		check++;
	}
	if (thisCube.Back[2][1] == thisCube.Back[1][1]) {
		check++;
	}
	if (thisCube.Back[1][2] == thisCube.Back[1][1]) {
		check++;
	}
	if (check == 4) {
		fit += 2;
	}
	check = 0;
	if (thisCube.Left[0][1] == thisCube.Left[1][1]) {
		check++;
	}
	if (thisCube.Left[1][0] == thisCube.Left[1][1]) {
		check++;
	}
	if (thisCube.Left[2][1] == thisCube.Left[1][1]) {
		check++;
	}
	if (thisCube.Left[1][2] == thisCube.Left[1][1]) {
		check++;
	}
	if (check == 4) {
		fit += 2;
	}
	check = 0;
	if (thisCube.Right[0][1] == thisCube.Right[1][1]) {
		check++;
	}
	if (thisCube.Right[1][0] == thisCube.Right[1][1]) {
		check++;
	}
	if (thisCube.Right[2][1] == thisCube.Right[1][1]) {
		check++;
	}
	if (thisCube.Right[1][2] == thisCube.Right[1][1]) {
		check++;
	}
	if (check == 4) {
		fit += 2;
	}
	check = 0;
	if (thisCube.Up[0][1] == thisCube.Up[1][1]) {
		check++;
	}
	if (thisCube.Up[1][0] == thisCube.Up[1][1]) {
		check++;
	}
	if (thisCube.Up[2][1] == thisCube.Up[1][1]) {
		check++;
	}
	if (thisCube.Up[1][2] == thisCube.Up[1][1]) {
		check++;
	}
	if (check == 4) {
		fit += 2;
	}
	check = 0;
	if (thisCube.Down[0][1] == thisCube.Down[1][1]) {
		check++;
	}
	if (thisCube.Down[1][0] == thisCube.Down[1][1]) {
		check++;
	}
	if (thisCube.Down[2][1] == thisCube.Down[1][1]) {
		check++;
	}
	if (thisCube.Down[1][2] == thisCube.Down[1][1]) {
		check++;
	}
	if (check == 4) {
		fit += 2;
	}
	// 1 * 18 horizontal rows
	for (int r = 0; r < 3; r++) {
		if (thisCube.Front[r][0] == thisCube.Front[r][1] && thisCube.Front[r][0] == thisCube.Front[r][2]) {
			fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Back[r][0] == thisCube.Back[r][1] && thisCube.Back[r][0] == thisCube.Back[r][2]) {
			fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Left[r][0] == thisCube.Left[r][1] && thisCube.Left[r][0] == thisCube.Left[r][2]) {
			fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Right[r][0] == thisCube.Right[r][1] && thisCube.Right[r][0] == thisCube.Right[r][2]) {
			fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Up[r][0] == thisCube.Up[r][1] && thisCube.Up[r][0] == thisCube.Up[r][2]) {
			fit++;
		}
	}
	for (int r = 0; r < 3; r++) {
		if (thisCube.Down[r][0] == thisCube.Down[r][1] && thisCube.Down[r][0] == thisCube.Down[r][2]) {
			fit++;
		}
	}
	// 1 * 18 vertical rows
	for (int c = 0; c < 3; c++) {
		if (thisCube.Front[0][c] == thisCube.Front[1][c] && thisCube.Front[0][c] == thisCube.Front[2][c]) {
			fit++;
		}
	}
	for (int c = 0; c < 3; c++) {
		if (thisCube.Back[0][c] == thisCube.Back[1][c] && thisCube.Back[0][c] == thisCube.Back[2][c]) {
			fit++;
		}
	}
	for (int c = 0; c < 3; c++) {
		if (thisCube.Left[0][c] == thisCube.Left[1][c] && thisCube.Left[0][c] == thisCube.Left[2][c]) {
			fit++;
		}
	}
	for (int c = 0; c < 3; c++) {
		if (thisCube.Right[0][c] == thisCube.Right[1][c] && thisCube.Right[0][c] == thisCube.Right[2][c]) {
			fit++;
		}
	}
	for (int c = 0; c < 3; c++) {
		if (thisCube.Up[0][c] == thisCube.Up[1][c] && thisCube.Up[0][c] == thisCube.Up[2][c]) {
			fit++;
		}
	}
	for (int c = 0; c < 3; c++) {
		if (thisCube.Down[0][c] == thisCube.Down[1][c] && thisCube.Down[0][c] == thisCube.Down[2][c]) {
			fit++;
		}
	}
	if (fit == 0) {
		fit = 1;
	}
	return fit;
}

// Only used in reproduce
Population selection(List<Population> pop, int initialPop) {
	double r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if (r == 1) {
		double t = 0.01;
		r = r - t;
	}
	pop.resetCurrent();
	for (int a = 0; a < initialPop; a++) {
		if (r < pop.getCurrent().probFit) {
			return pop.getCurrent();
		}
		pop.nextCurrent();
	}

	// if it doesn't work
	cout << "Error in selection" << endl;
	Population error;
	return error;
}

List<Population> reproduce(List<Population> pop, int initialPop, double selectPercent) {
	List<Population> newPop;

	// set all selecteds to false
	pop.resetCurrent();
	for (int a = 0; a < initialPop; a++) {
		Population temp = pop.getCurrent();
		temp.selected = false;
		pop.setCurrent(temp);
		pop.nextCurrent();
	}

	for (float a = 0; a < initialPop * selectPercent; a++) {
		double bestFit = -1;
		int bestPop = NULL;
		pop.resetCurrent();
		for (int b = 0; b < initialPop; b++) {
			if (pop.getCurrent().fitness > bestFit && pop.getCurrent().selected == false) {
				bestFit = pop.getCurrent().fitness;
				bestPop = b;
				
				Population temp = pop.getCurrent();
				temp.selected = true;
				pop.setCurrent(temp);
			}

			pop.nextCurrent();
		}
		Population tempPop = pop.getAt(bestPop);
		Genome tempGene = tempPop.networks.copy();
		tempPop.networks = tempGene;
		newPop.newNodeTail(tempPop);

		// so that best pop isnt grabbed again
		tempPop.fitness = -1;
		pop.setAt(bestPop, tempPop);
	}

	for (double a = 0; a < initialPop - (initialPop * selectPercent); a++) {
		Population tempPop = selection(pop, initialPop);
		Genome tempGene = tempPop.networks.copy();
		tempPop.networks = tempGene;
		newPop.newNodeTail(tempPop);
	}
	return pop;
	

}

void mutate(List<Population> &pop, int mutatePercent, int trainVnew) {
	/* Things to mutate:
		- Add Node
		- Remove Node
		- Add Connection
		- Remove Connection
		More likely {
		- Change Weight
		- Change Bias
		}
	*/

	// when finding rand()% of a size, size returns the abs num (not including 0), rand returns 0 to that abs num making it work out
	for (int a = 0; a < pop.getListSize(); a++) {
		// test if pop[a] get mutated
		if (rand() % 100 <= mutatePercent) {
			// pop[a] is getting mutated, test if it's getting trained or making a new network
			if (rand() % 100 <= trainVnew) {
				// pop[a] is getting trained, test whether a weight or bias is getting changed
				if (rand() % 100 <= 50) {
					// A connection's weight is getting changed, test which connection
					int randConnection = rand() % pop.getAt(a).networks.getConnectionSize();
					// Found which connection, test by how much the weight is being slightly changed (between .5 and 1.5)
					int x = rand() % 10;
					//.5 + 1 / (1 + e ^ -(x - 5))
					Population temp = pop.getAt(a);
					temp.networks.setConnectionWeight(randConnection, pop.getAt(a).networks.getConnectionWeight(randConnection) * (.5 + 1 / (1 + pow(exp(1.0), -(x - 5)))));
					pop.setAt(a, temp);
				}
				else {
					// A bias is getting changed, test which bias
					int randBias = rand() % pop.getAt(a).networks.getNodesSize();
					// Found which bias, test by how much the weight is being slightly changed (between .5 and 1.5)
					int x = rand() % 10;
					pop.getAt(a).networks.setNodeBias(randBias, pop.getAt(a).networks.getNodeBias(randBias) * (.5 + 1 / (1 + pow(exp(1.0), -(x - 5)))));
				}
			}
			else {
				// pop[a] is getting a new network, test whether something will be added or destroyed
				if (rand() % 3 != 0) {
					// Addition!! test whether a node or connection will be added
					if (/*rand() % 2*/ 1 == 0) {
						// a node will be added, test what existing connection the node will be added to
						int randConnection = rand() % pop.getAt(a).networks.getConnectionSize();
						// Found which connection, add it
						Population tempPop = pop.getAt(a);
						tempPop.networks.addNode(randConnection);
						pop.setAt(a, tempPop);
					}
					else {
						// a connection will be added, test if it's input will be from an input node or hidden node
						if (rand() % pop.getAt(a).networks.getInNodeSize() + (pop.getAt(a).networks.getNodesSize() - 13) < pop.getAt(a).networks.getInNodeSize()) { // Change if 13 changes
							// the in connection will be an input node, now find in and out
							int randIn = rand() % pop.getAt(a).networks.getInNodeSize();
							int randOut = rand() % pop.getAt(a).networks.getNodesSize();
							Population temp = pop.getAt(a);
							temp.networks.addConnection(-randIn, randOut);
							pop.setAt(a, temp);;
						}
						else {
							// the in connection will be a hidden node
							int randIn = 13 + (rand() % pop.getAt(a).networks.getNodesSize() - 13); // change if 13 changes
							int randOut = rand() % pop.getAt(a).networks.getNodesSize();
							Population temp = pop.getAt(a);
							temp.networks.addConnection(randIn, randOut);
							pop.setAt(a, temp);
						}
					}
				}
				else {
					// Destruction!! test whether a node or connection will be destroyed
								/*if (rand() % 1 == 0) {
									// a node will be destructioned! test what hidden node will be destroyed
									int randNode = rand() % 13 + (rand() % pop[a].networks.getNodesSize() - 13);
						
								}
								else {*/
						
					
					// a connection will be destructioned! test what connection will be destroyed
					int randConnection = rand() % pop.getAt(a).networks.getConnectionSize();
					pop.getAt(a).networks.switchConnectionActivity(randConnection);
					}
				}
			}
		}
	}
