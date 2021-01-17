#pragma once
#include <iostream>
#include <stdlib.h>
#include "Population.h"

using namespace std;

void outputCube(Cube thisCube) {
	for (int r = 0; r < 3; r++) {
		cout << "          ";
		for (int c = 0; c < 3; c++) {
			cout << thisCube.Up[r][c];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int r = 0; r < 3; r++) {
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << thisCube.Left[r][c];
			cout << " ";
		}
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << thisCube.Front[r][c];
			cout << " ";
		}
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << thisCube.Right[r][c];
			cout << " ";
		}
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << thisCube.Back[r][c];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int r = 2; r >= 0; r--) {
		cout << "          ";
		for (int c = 0; c < 3; c++) {
			cout << thisCube.Down[r][c];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}