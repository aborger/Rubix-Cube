#include "Cube.h"


#pragma once
// Constructor, gives each cubie color
Cube::Cube()
{
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Front[r][c] = 'B';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Back[r][c] = 'G';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Left[r][c] = 'O';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Right[r][c] = 'R';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Up[r][c] = 'Y';
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Down[r][c] = 'W';
		}
	}
}

// Move and swap are used to perform notation(moves)
void Cube::Move(char &a, char &b, char &c, char &d) {
	int temp = a;
	a = b;
	b = c;
	c = d;
	d = temp;
}
void Cube::Swap(char &a, char &b) {
	int temp = a;
	a = b;
	b = temp;
}


// Moves Notations
void Cube::L() {
	for (int a = 0; a < 3; a++) {
		Move(Front[a][0], Up[a][0], Back[a][0], Down[a][0]);
		Move(Left[0][a], Left[a][0], Left[2][a], Left[a][2]);
	}
	Swap(Up[0][0], Up[2][0]);
	Swap(Down[0][0], Down[2][0]);
	Swap(Left[0][2], Left[2][2]);
}
void Cube::l() {
	for (int a = 0; a < 3; a++) {
		Move(Front[a][0], Down[a][0], Back[a][0], Up[a][0]);
		Move(Left[a][2], Left[2][a], Left[a][0], Left[0][a]);
	}
	Swap(Front[0][0], Front[2][0]);
	Swap(Back[0][0], Back[2][0]);
	Swap(Left[2][0], Left[2][2]);
}
void Cube::R() {
	for (int a = 0; a < 3; a++) {
		Move(Front[a][2], Down[a][2], Back[a][2], Up[a][2]);
		Move(Right[0][a], Right[a][0], Right[2][a], Right[a][2]);
	}
	Swap(Front[0][2], Front[2][2]);
	Swap(Back[0][2], Back[2][2]);
	Swap(Right[0][2], Right[2][2]);
}
void Cube::r() {
	for (int a = 0; a < 3; a++) {
		Move(Front[a][2], Up[a][2], Back[a][2], Down[a][2]);
		Move(Right[a][2], Right[2][a], Right[a][0], Right[0][a]);
	}
	Swap(Up[0][2], Up[2][2]);
	Swap(Down[0][2], Down[2][2]);
	Swap(Right[2][0], Right[2][2]);
}
void Cube::U() {
	for (int a = 0; a < 3; a++) {
		Move(Front[0][a], Right[0][a], Back[0][a], Left[0][a]);
		Move(Up[0][a], Up[a][0], Up[2][a], Up[a][2]);
	}
	Swap(Right[0][0], Right[0][2]);
	Swap(Back[0][0], Back[0][2]);
	Swap(Up[0][2], Up[2][2]);
}
void Cube::u() {
	for (int a = 0; a < 3; a++) {
		Move(Front[0][a], Left[0][a], Back[0][a], Right[0][a]);
		Move(Up[a][2], Up[2][a], Up[a][0], Up[0][a]);
	}
	Swap(Left[0][0], Left[0][2]);
	Swap(Back[0][0], Back[0][2]);
	Swap(Up[2][0], Up[2][2]);
}
void Cube::D() {
	for (int a = 0; a < 3; a++) {
		Move(Front[2][a], Left[2][a], Back[2][a], Right[2][a]);
		Move(Down[0][a], Down[a][2], Down[2][a], Down[a][0]);
	}
	Swap(Left[2][0], Left[2][2]);
	Swap(Back[2][0], Back[2][2]);

	Swap(Down[2][0], Down[2][2]);
	Swap(Down[0][0], Down[2][0]);
}
void Cube::d() {
	for (int a = 0; a < 3; a++) {
		Move(Front[2][a], Right[2][a], Back[2][a], Left[2][a]);
		Move(Down[2][a], Down[a][2], Down[0][a], Down[a][0]);
	}
	Swap(Back[2][0], Back[2][2]);
	Swap(Right[2][0], Right[2][2]);
	Swap(Down[2][2], Down[0][2]);
}
void Cube::F() {
	for (int a = 0; a < 3; a++) {
		Move(Up[2][a], Left[a][2], Down[2][a], Right[a][0]);
		Move(Front[0][a], Front[a][0], Front[2][a], Front[a][2]);
	}
	Swap(Up[2][0], Up[2][2]);
	Swap(Down[2][0], Down[2][2]);
	Swap(Front[0][2], Front[2][2]);
}
void Cube::f() {
	for (int a = 0; a < 3; a++) {
		Move(Up[2][a], Right[a][0], Down[2][a], Left[a][2]);
		Move(Front[a][2], Front[2][a], Front[a][0], Front[0][a]);
	}
	Swap(Front[2][0], Front[2][2]);
	Swap(Left[0][2], Left[2][2]);
	Swap(Right[0][0], Right[2][0]);
}
void Cube::B() {
	for (int a = 0; a < 3; a++) {
		Move(Up[0][a], Right[a][2], Down[0][a], Left[a][0]);
		Move(Back[a][2], Back[2][a], Back[a][0], Back[0][a]);
	}
	Swap(Left[0][0], Left[2][0]);
	Swap(Right[0][2], Right[2][2]);
	Swap(Back[2][0], Back[2][2]);
}
void Cube::b() {
	for (int a = 0; a < 3; a++) {
		Move(Up[0][a], Left[a][0], Down[0][a], Right[a][2]);
		Move(Back[0][a], Back[a][0], Back[2][a], Back[a][2]);
	}
	Swap(Up[0][0], Up[0][2]);
	Swap(Down[0][0], Down[0][2]);
	Swap(Back[0][2], Back[2][2]);
}

// Takes letter and performs move on objects cube
void Cube::pickMove(char var) {
	if (var == 'L') {
		L();
	}
	if (var == 'l') {
		l();
	}
	if (var == 'R') {
		R();
	}
	if (var == 'r') {
		r();
	}
	if (var == 'U') {
		U();
	}
	if (var == 'u') {
		u();
	}
	if (var == 'D') {
		D();
	}
	if (var == 'd') {
		d();
	}
	if (var == 'F') {
		F();
	}
	if (var == 'f') {
		f();
	}
	if (var == 'B') {
		B();
	}
	if (var == 'b') {
		b();
	}
	if (var == ' ') {
		// do nothing
	}
}


Cube::~Cube()
{
}
