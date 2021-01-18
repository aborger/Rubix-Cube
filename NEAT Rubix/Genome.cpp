#include "Genome.h"


using namespace std;
// create 54 input nodes and 13 output nodes and 1 connection
Genome::Genome()
{
}

void Genome::randFill() {

	char faces[6] = { 'F', 'B', 'L', 'R', 'U', 'D' };
	for (int f = 0; f < 6; f++) {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				InputNode *Temp = NULL;
				Temp = new InputNode(faces[f], r, c);
				InNodes.newNodeTail(*Temp);
			}
		}
	}
	for (int a = 0; a < 14; a++) {
		Node *temp = NULL;
		temp = new Node;
		Nodes.newNodeTail(*temp);
	}

	Nodes.getAt(13).newIn(0);
	int in = rand() % 54;
	int out = rand() % 13;
	double weight = 1;
	Connection *temp;
	Connection *temp2;
	// InNodes are negative
	temp = new Connection(in * -1, 13, weight);
	temp2 = new Connection(13, out, weight);
	Connections.newNodeTail(*temp);
	Connections.newNodeTail(*temp2);

	Nodes.getAt(out).newIn(1);
	Nodes.getAt(out).newOut(0);
}


// Getters
	// Takes the chance for each move and picks one
void Genome::getMove(List<char> &Moves, int numMoves) {
	int sum = 0;
	
	List <double> moveProb;
	// adds fitness to moveProb
	for (int whatMove = 0; whatMove < 13; whatMove++) {
		double output = getOutput(whatMove);
		sum += output;
		moveProb.newNodeTail(output);
	}

	int bestMove = -1;
	double bestMoveProbability = -1;

	//picks best
	for (int a = 0; a < 13; a++) {
		double temp = moveProb.getAt(a);
		if (temp > bestMoveProbability) {
			bestMoveProbability = temp;
			bestMove = a;
		}
	}




	if (bestMove == 0) {
		Moves.newNodeTail('L');
	}
	else if (bestMove == 1) {
		Moves.newNodeTail('l');
	}
	else if (bestMove == 2) {
		Moves.newNodeTail('R');
	}
	else if (bestMove == 3) {
		Moves.newNodeTail('r');
	}
	else if (bestMove == 4) {
		Moves.newNodeTail('U');
	}
	else if (bestMove == 5) {
		Moves.newNodeTail('u');
	}
	else if (bestMove == 6) {
		Moves.newNodeTail('D');
	}
	else if (bestMove == 7) {
		Moves.newNodeTail('d');
	}
	else if (bestMove == 8) {
		Moves.newNodeTail('F');
	}
	else if (bestMove == 9) {
		Moves.newNodeTail('f');
	}
	else if (bestMove == 10) {
		Moves.newNodeTail('B');
	}
	else if (bestMove == 11) {
		Moves.newNodeTail('b');
	}
	else if (bestMove == 12) {
		Moves.newNodeTail(' ');
	}
	else {
		Moves.newNodeTail(' ');
	}

	// uses moves on cube
	thisCube.pickMove(Moves.getBack());

}

List <InputNode> Genome::getINodes() {
	return InNodes;
}
List <Node> Genome::getNodes() {
	return Nodes;
}
List <Connection> Genome::getConnections() {
	return Connections;
}


	// Gets Percentage of each move for final or output of node
// ERORR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
// outputs same letter twice
double Genome::getOutput(int whatNode) {
	if (whatNode < 0) {
		// Negative because Innodes or negative
		return InNodes.getAt(-1 * whatNode).getValue(thisCube);
	} else {
		double x = 0;
		int NumInConnect = Nodes.getAt(whatNode).getInConnectorSize();
		for (int a = 0; a < NumInConnect; a++) {
			// also seperated for clarity
			int inConnector = Nodes.getAt(whatNode).getInConnectors(a);
			if (Connections.getAt(inConnector).getAbled() == true) {// if the connection is enabled then calculate
				// multiply connections in by its weight, could be smaller but spread out so its easier to read and debug
				int inConnector = Nodes.getAt(whatNode).getInConnectors(a); // finds this nodes connectors that input to it
				int theNode = Connections.getAt(inConnector).getIn(); // gets the connectors in

				double ConnectorIn = getOutput(theNode);
				double ConnectorWeight = Connections.getAt(inConnector).getWeight();
				x += ConnectorIn * ConnectorWeight;
			}
		}
		x += Nodes.getAt(whatNode).getBias();
		return 1/(1 + pow(exp(1.0), x));
	}
}

int Genome::getConnectionSize() {
	return Connections.getListSize();
}

double Genome::getConnectionWeight(int whatConnection) {
	return Connections.getAt(whatConnection).getWeight();
}

int Genome::getNodesSize() {
	return Nodes.getListSize();
}

double Genome::getNodeBias(int whatNode) {
	return Nodes.getAt(whatNode).getBias();
}

int Genome::getInNodeSize() {
	return InNodes.getListSize();
}


/*void Genome::getNodeInC(int whatNode, List<int> &connects) {
	connects.resize(Nodes.getAt(whatNode).getInConnectorSize());
	for (int a = 0; a < connects.getListSize(); a++) {
		connects.setAt(a, Nodes.getAt(whatNode).getInConnectors(a));
	}
}
void Genome::getNodeOutC(int whatNode, List<int> &connects) {
	connects.resize(Nodes.getAt(whatNode).getOutConnectorSize());
	for (int a = 0; a < connects.getListSize(); a++) {
		connects.setAt(a, Nodes.getAt(whatNode).getOutConnectors(a));
	}
}*/

// returns the copy
Genome Genome::copy() {
	Genome newCopy;
	/* To be copied
	List <InputNode> InNodes;
	List <Node> Nodes;
	List <Connection> Connections;

	Cube thisCube;*/

	InNodes.resetCurrent();
	for (int a = 0; a < InNodes.getListSize(); a++) {
		newCopy.InNodes.newNodeTail(InNodes.getCurrent());
		InNodes.nextCurrent();
	}


	Nodes.resetCurrent();
	for (int a = 0; a < Nodes.getListSize(); a++) {
		newCopy.Nodes.newNodeTail(Nodes.getCurrent());
		Nodes.nextCurrent();
	}


	Connections.resetCurrent();
	for (int a = 0; a < Connections.getListSize(); a++) {
		newCopy.Connections.newNodeTail(Connections.getCurrent());
		Connections.nextCurrent();
	}

	return newCopy;
}


void Genome::outputGenes() {
	cout << "Nodes: " << endl;
	for (int a = 0; a < Nodes.getListSize(); a++) {
		cout << "   " << a << "  ";
	}
	cout << "  " << endl;
	for (int a = 0; a < 120; a++) {
		cout << "-";
	}
	for (int a = 0; a < Nodes.getListSize(); a++) {
		cout << "   " << Nodes.getAt(a).getBias() << "  ";
	}

	cout << "  " << endl;
	for (int a = 0; a < 120; a++) {
		cout << "=";
	}

	cout << "Connections: " << endl;
	for (int a = 0; a < Connections.getListSize(); a++) {
		cout << "      " << a << "   ";
	}
	cout << endl;
	for (int a = 0; a < 120; a++) {
		cout << "-";
	}
	for (int a = 0; a < Connections.getListSize(); a++) {
		cout << "  " << Connections.getAt(a).getIn() << " " << Connections.getAt(a).getWeight() << " " << Connections.getAt(a).getOut() << " ";
	}
	cout << "  " << endl << endl;
}

// Setters
void Genome::setConnectionWeight(int whatConnection, double newWeight) {
	Connections.getAt(whatConnection).setWeight(newWeight);
}

void Genome::setNodeBias(int whatNode, double newBias) {
	Node temp = Nodes.getAt(whatNode);
	temp.setBias(newBias);
	Nodes.setAt(whatNode, temp);

}

void Genome::addNode(int whatConnection) {
	// whatConnection get new node as output
	Node *newN = NULL;
	newN = new Node;
	newN->newIn(whatConnection);
	Nodes.newNodeTail(*newN);

	// new connection get new node as input and whatConnections old output as output
	Connection *newC = NULL;
	newC = new Connection(Nodes.getListSize() - 1, Connections.getAt(whatConnection).getOut(), 1);
	Connections.newNodeTail(*newC);
	Nodes.getBack().newOut(Connections.getListSize() - 1);
	Connections.getAt(whatConnection).setOut(Nodes.getListSize() - 1);
}

void Genome::addConnection(int in, int out) {
	Connection *newC = NULL;
	newC = new Connection(in, out, 1);
	// size returns one more, so when a new one is added newIn will point to correct connection
	Node temp = Nodes.getAt(out);
	int size = Connections.getListSize();
	temp.newIn(size);
	Nodes.setAt(out, temp);
	Connections.newNodeTail(*newC);
}

void Genome::switchConnectionActivity(int whichConnection) {
	Connections.getAt(whichConnection).switchAbled();
}
Genome::~Genome()
{
}
