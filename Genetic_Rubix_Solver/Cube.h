#pragma once
class Cube
{
public:
	char Front[3][3];
	char Back[3][3];
	char Left[3][3];
	char Right[3][3];
	char Up[3][3];
	char Down[3][3];

	Cube();

	void Move(char &a, char &b, char &c, char &d);
	void Swap(char &a, char &b);


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

