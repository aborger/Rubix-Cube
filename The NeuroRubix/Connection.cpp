#include "Connection.h"


Connection::Connection() {}
Connection::Connection(int in, int out, double weight)
{
	In = in;
	Out = out;
	Weight = weight;
}

// Getters
int Connection::getIn() {
	return In;
}
int Connection::getOut() {
	return Out;
}
double Connection::getWeight() {
	return Weight;
}
bool Connection::getAbled() {
	return Abled;
}
// Setters
void Connection::setIn(int newIn) {
	In = newIn;
}
void Connection::setOut(int newOut) {
	Out = newOut;
}
void Connection::setWeight(double newWeight) {
	Weight = newWeight;
}
void Connection::switchAbled() {
	Abled = !Abled;
}


Connection::~Connection()
{
}
