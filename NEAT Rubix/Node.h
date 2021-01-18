#pragma once
#include "List.h"
#include "Connection.h"
//#include "Genome.h"

using namespace std;

class Node
{
private:
	List<int> inConnectors;
	List<int> outConnectors;
	double bias = 1;
public:
	Node();
	// Getters
	int getInConnectors(int element);
	int getInConnectorSize();
	int getOutConnectors(int element);
	int getOutConnectorSize();
	double getBias();

	// Setters
	void newIn(int in);
	void newOut(int out);
	void setBias(double newBias);
	~Node();
};

