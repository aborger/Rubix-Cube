#include "Node.h"



Node::Node()
{
}

// Getters
int Node::getInConnectors(int element) {
	return inConnectors.getAt(element);
}
int Node::getInConnectorSize() {
	return inConnectors.getListSize();
}
int Node::getOutConnectors(int element) {
	return outConnectors.getAt(element);
}
int Node::getOutConnectorSize() {
	return inConnectors.getListSize();
}
double Node::getBias() {
	return bias;
}

// Setters
void Node::newIn(int in) {
	inConnectors.newNodeTail(in);
}
void Node::newOut(int out) {
	outConnectors.newNodeTail(out);
}
void Node::setBias(double newBias) {
	bias = newBias;
}

Node::~Node()
{
}
