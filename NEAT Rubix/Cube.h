#pragma once
class Cube
{
private:
	void Move(char &a, char &b, char &c, char &d);
	void Swap(char &a, char &b);
public:

	// A 2d array each corresponding to each side of the cube, the letter corresponds to a color
	char Front[3][3];
	char Back[3][3];
	char Left[3][3];
	char Right[3][3];
	char Up[3][3];
	char Down[3][3];

	Cube();
	// Performs 25 random moves on cube
	void scrambleCube();


	void outputCube();


	// Moves to perform on the cube
	void L();
	void l();
	void R();
	void r();
	void U();
	void u();
	void D();
	void d();
	void F();
	void f();
	void B();
	void b();

	void pickMove(char var);

	~Cube();
};
