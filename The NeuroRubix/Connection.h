#pragma once
class Connection
{
private:
	int In;
	int Out;
	double Weight;
	bool Abled;
public:
	Connection();
	Connection(int In, int Out, double Weight);

	// Getters
	int getIn();
	int getOut();
	double getWeight();
	bool getAbled();
	// Setters
	void setIn(int newIn);
	void setOut(int newOut);
	void setWeight(double newWeight);
	void switchAbled();

	~Connection();
};

