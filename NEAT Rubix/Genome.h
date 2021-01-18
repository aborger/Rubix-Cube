#pragma once
#include "List.h"
#include "InputNode.h"
#include "Node.h"
#include "Connection.h"
#include <time.h>
#include <iostream>


using namespace std;

class Genome
{
private:
	// 0 - 12 Nodes are output nodes following the order:
	// L, l, R, r, U, u, D, d, F, f, B, b, ' '
	List <InputNode> InNodes;
	List <Node> Nodes;
	List <Connection> Connections;

	Cube thisCube;
public:
	Genome();


	void randFill();

	// Getters
	List <InputNode> getINodes();
	List <Node> getNodes();
	List <Connection> getConnections();
	void getMove(List<char> &Moves, int numMoves);
	double getOutput(int whatNode);
	int getConnectionSize();
	double getConnectionWeight(int whatConnection);
	int getNodesSize();
	double getNodeBias(int whatNode);
	int getInNodeSize();
	//void getNodeInC(int whatNode, List<int> &connects);
	//void getNodeOutC(int whatNode, List<int> &connects);

	Genome copy();


	void outputGenes();
	// Setters
	void setConnectionWeight(int whatConnection, double newWeight);
	void setNodeBias(int whatNode, double newBias);
	void addNode(int whatConnection);
	void addConnection(int in, int out);
	void switchConnectionActivity(int whichConnection);


	~Genome();
};

