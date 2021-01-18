
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

using namespace std;

// Cube Arrays

// Test
/*int Front[3][3];
int Back[3][3];
int Left[3][3];
int Right[3][3];
int Up[3][3];
int Down[3][3];*/


char Front[3][3];
char Back[3][3];
char Left[3][3];
char Right[3][3];
char Up[3][3];
char Down[3][3];

int moveCount = 0;


/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::											Function Prototypes										::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void input();
void solvedCube();
void scrambleCube();
void outputCube();


void Move(char &a, char &b, char &c, char &d);
void Swap(char &a, char &b);

void Test();
//------------------------------------------- Cube Notations --------------------------------------------------------||
void L();
void Lpr();
void R();
void Rpr();
void U();
void Upr();
void D();
void Dpr();
void F();
void Fpr();
void B();
void Bpr();
void T();
void Tpr();
//----------------------------------------------- Solving -----------------------------------------------------------||
void whiteCross();
void whiteFace();
void find(char col1, char col2);
void PlaceF2L();
void findCenter(char col1, char col2);
void YCross();
void YCorners();
void PLL();


int tooManyTurn = 0;
bool maybeGood = 0;
/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::												Main												::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

int main() {
	scrambleCube();
	cout << "scrambled-------------------------------------------------" << endl;
	outputCube();
	system("PAUSE");
	moveCount = 0;
	cout << endl << moveCount << endl;
	whiteCross();
	cout << "Cross Complete--------------------------------------------------------------" << endl;
	outputCube();
	cout << endl << moveCount << endl;
	while (!(Down[0][0] == 'W' && Down[0][1] == 'W' && Down[0][2] == 'W' && Down[1][0] == 'W' && Down[1][1] == 'W' && Down[1][2] == 'W' && Down[2][0] == 'W' && Down[2][1] == 'W' && Down[2][2] == 'W' && Front[1][1] == Front[1][0] && Front[1][1] == Front[1][2] && Front[1][1] == Front[2][0] && Front[1][1] == Front[2][1] && Front[1][1] == Front[2][2] && Right[1][1] == Right[1][0] && Right[1][1] == Right[1][2] && Right[1][1] == Right[2][0] && Right[1][1] == Right[2][1] && Right[1][1] == Right[2][2] && Left[1][1] == Left[1][0] && Left[1][1] == Left[1][2] && Left[1][1] == Left[2][0] && Left[1][1] == Left[2][1] && Left[1][1] == Left[2][2] && Back[1][1] == Back[1][0] && Back[1][1] == Back[1][2] && Back[1][1] == Back[2][0] && Back[1][1] == Back[2][1] && Back[1][1] == Back[2][2])) {
		whiteFace();
	}
	cout << endl << moveCount << endl;
	cout << "F2L Done-----------------------------------" << endl;
	YCross();
	cout << "YCross Done-----------------------" << endl;
	outputCube();
	YCorners();
	cout << "YCorners Done----------------------------------" << endl;
	outputCube();
	cout << moveCount << endl;
	//system("PAUSE");
	PLL();
	outputCube();
	cout << "Number of moves: " << moveCount << endl;
	system("PAUSE");
}

/*
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::											Functions												::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void input(){
	cout << "Input front face (typewriter style)" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cin >> Front[r][c];
		}
	}
	cout << "Input back face (typewriter style)" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cin >> Back[r][c];
		}
	}
	cout << "Input left face (typewriter style)" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cin >> Left[r][c];
		}
	}
	cout << "Input right face (typewriter style)" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cin >> Right[r][c];
		}
	}
	cout << "Input up face (typewriter style)" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cin >> Up[r][c];
		}
	}
	cout << "Input down face (typewriter style)" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cin >> Down[r][c];
		}
	}

	//system("PAUSE");
}
void solvedCube() {
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
void scrambleCube() {
	solvedCube();
	srand(time(NULL));
	for (int a = 0; a < 25; a++) {
		int Random = rand() % 12;
		if (Random == 0) {
			L();
		}
		if (Random == 1) {
			Lpr();
		}
		if (Random == 2) {
			R();
		}
		if (Random == 3) {
			Rpr();
		}
		if (Random == 4) {
			U();
		}
		if (Random == 5) {
			Upr();
		}
		if (Random == 6) {
			D();
		}
		if (Random == 7) {
			Dpr();
		}
		if (Random == 8) {
			F();
		}
		if (Random == 9) {
			Fpr();
		}
		if (Random == 10) {
			B();
		}
		if (Random == 11) {
			Bpr();
		}
	}
}
void outputCube() {
	for (int r = 0; r < 3; r++) {
		cout << "          ";
		for (int c = 0; c < 3; c++) {
			cout << Up[r][c];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int r = 0; r < 3; r++) {
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << Left[r][c];
			cout << " ";
		}
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << Front[r][c];
			cout << " ";
		}
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << Right[r][c];
			cout << " ";
		}
		cout << "  ";
		for (int c = 0; c < 3; c++) {
			cout << Back[r][c];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int r = 2; r >= 0; r--) {
		cout << "          ";
		for (int c = 0; c < 3; c++) {
			cout << Down[r][c];
			cout << " ";
		}
		cout << endl;
	}
}
// Test
/*void Move(int &a, int &b, int &c, int &d) {
	int temp = a;
	a = b;
	b = c;
	c = d;
	d = temp;
}
void Swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
*/
void Move(char &a, char &b, char &c, char &d) {
	int temp = a;
	a = b;
	b = c;
	c = d;
	d = temp;
}
void Swap(char &a, char &b) {
	int temp = a;
	a = b;
	b = temp;
}

void Test() {
	int a = 0;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Front[r][c] = a;
			a++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Back[r][c] = a;
			a++;
		}
	}
	for (int r = 0; r < 3; r++) {
		a++;
		for (int c = 0; c < 3; c++) {
			Left[r][c] = a;
			a++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Right[r][c] = a;
			a++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Up[r][c] = a;
			a++;
		}
	}
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Down[r][c] = a;
			a++;
		}
	}
}

//------------------------------------------- Cube Notations --------------------------------------------------------||

void L() {
	cout << "L" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[a][0], Up[a][0], Back[a][0], Down[a][0]);
		Move(Left[0][a], Left[a][0], Left[2][a], Left[a][2]);
	}
	Swap(Up[0][0], Up[2][0]);
	Swap(Down[0][0], Down[2][0]);
	Swap(Left[0][2], Left[2][2]);
	outputCube();
	moveCount++;
}
void Lpr() {
	cout << "Lpr" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[a][0], Down[a][0], Back[a][0], Up[a][0]);
		Move(Left[a][2], Left[2][a], Left[a][0], Left[0][a]);
	}
	Swap(Front[0][0], Front[2][0]);
	Swap(Back[0][0], Back[2][0]);
	Swap(Left[2][0], Left[2][2]);
	outputCube();
	moveCount++;
}
void R() {
	cout << "R" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[a][2], Down[a][2], Back[a][2], Up[a][2]);
		Move(Right[0][a], Right[a][0], Right[2][a], Right[a][2]);
	}
	Swap(Front[0][2], Front[2][2]);
	Swap(Back[0][2], Back[2][2]);
	Swap(Right[0][2], Right[2][2]);
	outputCube();
	moveCount++;
}
void Rpr(){
	cout << "Rpr" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[a][2], Up[a][2], Back[a][2], Down[a][2]);
		Move(Right[a][2], Right[2][a], Right[a][0], Right[0][a]);
	}
	Swap(Up[0][2], Up[2][2]);
	Swap(Down[0][2], Down[2][2]);
	Swap(Right[2][0], Right[2][2]);
	outputCube();
	moveCount++;
}
void U() {
	cout << "U" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[0][a], Right[0][a], Back[0][a], Left[0][a]);
		Move(Up[0][a], Up[a][0], Up[2][a], Up[a][2]);
	}
	Swap(Right[0][0], Right[0][2]);
	Swap(Back[0][0], Back[0][2]);
	Swap(Up[0][2], Up[2][2]);
	outputCube();
	moveCount++;
}
void Upr() {
	cout << "Upr" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[0][a], Left[0][a], Back[0][a], Right[0][a]);
		Move(Up[a][2], Up[2][a], Up[a][0], Up[0][a]);
	}
	Swap(Left[0][0], Left[0][2]);
	Swap(Back[0][0], Back[0][2]);
	Swap(Up[2][0], Up[2][2]);
	outputCube();
	moveCount++;
}
void D() {
	cout << "D" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[2][a], Left[2][a], Back[2][a], Right[2][a]);
		Move(Down[0][a], Down[a][2], Down[2][a], Down[a][0]);
	}
	Swap(Left[2][0], Left[2][2]);
	Swap(Back[2][0], Back[2][2]);

	Swap(Down[2][0], Down[2][2]);
	Swap(Down[0][0], Down[2][0]);
	outputCube();
	moveCount++;
}
void Dpr() {
	cout << "Dpr" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Front[2][a], Right[2][a], Back[2][a], Left[2][a]);
		Move(Down[2][a], Down[a][2], Down[0][a], Down[a][0]);
	}
	Swap(Back[2][0], Back[2][2]);
	Swap(Right[2][0], Right[2][2]);
	Swap(Down[2][2], Down[0][2]);
	outputCube();
	moveCount++;
}
void F() {
	cout << "F" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Up[2][a], Left[a][2], Down[2][a], Right[a][0]);
		Move(Front[0][a], Front[a][0], Front[2][a], Front[a][2]);
	}
	Swap(Up[2][0], Up[2][2]);
	Swap(Down[2][0], Down[2][2]);
	Swap(Front[0][2], Front[2][2]);
	outputCube();
	moveCount++;
}
void Fpr() {
	cout << "Fpr" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Up[2][a], Right[a][0], Down[2][a], Left[a][2]);
		Move(Front[a][2], Front[2][a], Front[a][0], Front[0][a]);
	}
	Swap(Front[2][0], Front[2][2]);
	Swap(Left[0][2], Left[2][2]);
	Swap(Right[0][0], Right[2][0]);
	outputCube();
	moveCount++;
}
void B() {
	cout << "B" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Up[0][a], Right[a][2], Down[0][a], Left[a][0]);
		Move(Back[a][2], Back[2][a], Back[a][0], Back[0][a]);
	}
	Swap(Left[0][0], Left[2][0]);
	Swap(Right[0][2], Right[2][2]);
	Swap(Back[2][0], Back[2][2]);
	outputCube();
	moveCount++;
}
void Bpr() {
	cout << "Bpr" << endl;
	for (int a = 0; a < 3; a++) {
		Move(Up[0][a], Left[a][0], Down[0][a], Right[a][2]);
		Move(Back[0][a], Back[a][0], Back[2][a], Back[a][2]);
	}
	Swap(Up[0][0], Up[0][2]);
	Swap(Down[0][0], Down[0][2]);
	Swap(Back[0][2], Back[2][2]);
	outputCube();
	moveCount++;
}
void T() {
	cout << "T" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Move(Front[r][c], Right[r][c], Back[r][c], Left[r][c]);
		}
		Move(Up[0][r], Up[r][0], Up[2][r], Up[r][2]);
		Swap(Up[0][2], Up[2][2]);
		Move(Down[0][r], Down[r][0], Down[2][r], Down[r][2]);
		Swap(Down[0][2], Down[2][2]);
		Swap(Back[r][0], Back[r][2]);
		Swap(Right[r][0], Right[r][2]);
	}
	outputCube();
	moveCount++;
}
void Tpr() {
	cout << "Tpr" << endl;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			Move(Front[r][c], Left[r][c], Back[r][c], Right[r][c]);
		}
		Move(Down[r][2], Down[2][r], Down[r][0], Down[0][r]);
		Swap(Down[2][0], Down[2][2]);
		Move(Up[r][2], Up[2][r], Up[r][0], Up[0][r]);
		Swap(Up[2][0], Up[2][2]);
		Swap(Back[r][0], Back[r][2]);
		Swap(Left[r][0], Left[r][2]);
	}
	outputCube();
	moveCount++;
}
void d() {
	T();
	Upr();
	outputCube();
	moveCount++;
}
void dpr() {
	Tpr();
	U();
	outputCube();
	moveCount++;
}
//---------------------------------------------- Solving --------------------------------------------------------||
//--------------------------------------------- White Cross -----------------------------------------------------||
// Infinite problem in white cross!!!!!!!!!!!!!!!1
// Take out T's!!
void whiteCross() {
	while (Down[0][1] != 'W' || Down[1][0] != 'W' || Down[1][2] != 'W' || Down[2][1] != 'W') {
		if (Up[2][1] == 'W') {
			if (Front[0][1] == Front[1][1]) {
				F();
				F();
			}
			else if (Front[0][1] == Right[1][1]) {
				Upr();
				R();
				R();
			}
			else if (Front[0][1] == Left[1][1]) {
				U();
				L();
				L();
			}
			else if (Front[0][1] == Back[1][1]) {
				U();
				U();
				B();
				B();
			}
		}
		if (Right[1][0] == 'W') {
			if (Front[1][2] == Front[1][1]) {
				F();
			}
			else {
				Fpr();
				if (Front[0][1] == Right[1][1]) {
					Upr();
					if (Right[1][0] == 'W') {
						F();
					}
					F();
					R();
					R();
				}
				else if (Front[0][1] == Left[1][1]) {
					U();
					if (Right[1][0] == 'W') {
						F();
					}
					F();
					L();
					L();
				}
				else if (Front[0][1] == Back[1][1]) {
					U();
					U();
					if (Right[1][0] == 'W') {
						F();
					}
					B();
					B();
				}
			}
		}
		if (Left[1][2] == 'W') {
			if (Front[1][0] == Front[1][1]) {
				Fpr();
			}
			else {
				F();
				if (Front[0][1] == Right[1][1]) {
					Upr();
					if (Left[1][2] == 'W') {
						Fpr();
					}
					R();
					R();
				}
				else if (Front[0][1] == Left[1][1]) {
					U();
					if (Left[1][2] == 'W') {
						Fpr();
					}
					L();
					L();
				}
				else if (Front[0][1] == Back[1][1]) {
					U();
					U();
					if (Left[1][2] == 'W') {
						Fpr();
					}
					B();
					B();
				}
			}
		}
		if (Front[0][1] == 'W') {
			if (Up[2][1] == Front[1][1]) {
				Upr();
				Rpr();
				F();
				R();
			}
			else {
				if (Up[2][1] == Right[1][1]) {
					F();
					Rpr();
					if (Left[1][2] == 'W') {
						Fpr();
					}
				}
				else if (Up[2][1] == Left[1][1]) {
					Fpr();
					L();
					if (Right[1][0] == 'W') {
						F();
					}
				}
				else if (Up[2][1] == Back[1][1]) {
					U();
					Lpr();
					B();
					if (Front[1][0] == 'W') {
						L();
					}
				}
			}
		}
		if (Down[1][2] == 'W') {
			if (Front[2][1] == Front[1][1]) {

			}
			else {
				F();
				F();
				if (Front[0][1] == Right[1][1]) {
					Upr();
					R();
					R();
				}
				else if (Front[0][1] == Left[1][1]) {
					U();
					L();
					L();
				}
				else if (Front[0][1] == Back[1][1]) {
					U();
					U();
					B();
					B();
				}
			}
		}
		if (Front[1][0] == 'W') {
			F();
			if (Left[1][2] == Front[1][1]) {
				Upr();
				Rpr();
				F();
				R();
			}
			else {
				if (Up[2][1] == Right[1][1]) {
					F();
					Rpr();
					if (Up[2][1] == 'W') {
						F();
						F();
					}
				}
				else if (Up[2][1] == Left[1][1]) {
					Fpr();
					L();
				}
				else if (Up[2][1] == Back[1][1]) {
					U();
					Lpr();
					B();
					if (Left[0][1] == 'W') {
						L();
						Fpr();
					}
				}
			}
		}
		if (Front[1][2] == 'W') {
			Fpr();
			if (Up[2][1] == Front[1][1]) {
				Upr();
				Rpr();
				F();
				R();
			}
			else {
				if (Up[2][1] == Right[1][1]) {
					F();
					Rpr();
				}
				else if (Up[2][1] == Left[1][1]) {
					Fpr();
					L();
					if (Up[2][1] == 'W') {
						F();
						F();
					}
				}
				else if (Up[2][1] == Back[1][1]) {
					U();
					Lpr();
					B();
					if (Right[1][0] == 'W') {
						F();
					}
				}
			}
		}
		if (Front[2][1] == 'W') {
			F();
			F();
			if (Down[0][1] == Front[1][1]) {
				Upr();
				Rpr();
				F();
				R();
			}
			else {
				if (Up[2][1] == Right[1][1]) {
					F();
					Rpr();
				}
				else if (Up[2][1] == Left[1][1]) {
					Fpr();
					L();
				}
				else if (Up[2][1] == Back[1][1]) {
					U();
					Lpr();
					B();
					if (Front[1][0] == 'W') {
						L();
					}
				}
			}
		}
	T();
	cout << endl;
	}
}
//------------------------------------------------- F2L ---------------------------------------------------------||
void whiteFace() {
	// 1 = Front Right, 2 = Front Left, 3 = Back Left, 4 = Back Right
	// Top Right Corner
	for (int a = 0; a < 4; a++) {
		cout << "Testing for white corners on face" << endl;
		if (Front[0][2] == 'W' || Up[2][2] == 'W' || Right[0][0] == 'W') {
			cout << "Top right is white" << endl;
			if (Front[0][2] == 'W') {
				findCenter(Up[2][2], Right[0][0]);
			}
			if (Up[2][2] == 'W') {
				findCenter(Front[0][2], Right[0][0]);
			}
			if (Right[0][0] == 'W') {
				findCenter(Up[2][2], Front[0][2]);
			}
			a = 5;
		}
		//  Bottom Right Corner
		else if (!(Front[1][1] == Front[2][2] && Right[1][1] == Right[2][0])) {
			if (Front[2][2] == 'W' || Down[2][2] == 'W' || Right[2][0] == 'W') {
				cout << "Bottom right is white" << endl;
				R();
				U();
				Rpr();
				Upr();
				if (Front[0][2] == 'W') {
					findCenter(Up[2][2], Right[0][0]);
				}
				if (Up[2][2] == 'W') {
					findCenter(Front[0][2], Right[0][0]);
				}
				if (Right[0][0] == 'W') {
					findCenter(Up[2][2], Front[0][2]);
				}
				a = 5;
			}
		}
		// Top Left Corner
		else if (Front[0][0] == 'W' || Up[2][0] == 'W' || Left[0][2] == 'W') {
			cout << "Top Left is white" << endl;
			Tpr();
			if (Front[0][2] == 'W') {
				findCenter(Up[2][2], Right[0][0]);
			}
			if (Up[2][2] == 'W') {
				findCenter(Front[0][2], Right[0][0]);
			}
			if (Right[0][0] == 'W') {
				findCenter(Up[2][2], Front[0][2]);
			}
			a = 5;
		}
		// Bottom Left Corner
		else if (!(Front[1][1] == Front[2][0] && Left[1][1] == Left[2][2])) {
			if (Front[2][0] == 'W' || Down[2][0] == 'W' || Left[2][2] == 'W') {
				cout << "Bottom Left is white" << endl;
				Tpr();
				R();
				U();
				Rpr();
				Upr();
				if (Front[0][2] == 'W') {
					findCenter(Up[2][2], Right[0][0]);
				}
				if (Up[2][2] == 'W') {
					findCenter(Front[0][2], Right[0][0]);
				}
				if (Right[0][0] == 'W') {
					findCenter(Up[2][2], Front[0][2]);
				}
				a = 5;
			}
		}
		if (a != 5) {
			T();
		}
	}
}
void findCenter(char col1, char col2) {
	// Front Right
	if ((Front[1][1] == col1 && Right[1][1] == col2) || (Front[1][1] == col2 && Right[1][1] == col1)) {
		cout << "Corner Placed" << endl;
	}
	// Back Right
	else if ((Right[1][1] == col1 && Back[1][1] == col2) || (Right[1][1] == col2 && Back[1][1] == col1)) {
		Upr();
		T();
		cout << "Corner Placed" << endl;
	}
	// Back Left
	else if ((Left[1][1] == col1 && Back[1][1] == col2) || (Left[1][1] == col2 && Back[1][1] == col1)) {
		U();
		U();
		Tpr();
		Tpr();
		cout << "Corner Placed" << endl;
	}
	// Front Left
	else if ((Front[1][1] == col1 && Left[1][1] == col2) || (Front[1][1] == col2 && Left[1][1] == col1)) {
		U();
		Tpr();
		cout << "Corner Placed" << endl;
	}
	find(col1, col2);
}
void find(char col1, char col2) {
		// Front Left
	if ((Front[1][0] == col1 && Left[1][2] == col2) || Front[1][0] == col2 && Left[1][2] == col1) {
		cout << "Found matching edge" << endl;
		F();
		U();
		Fpr();
	}
	// Front Right
	else if ((Front[1][2] == col1 && Right[1][0] == col2) || (Front[1][2] == col2 && Right[1][0] == col1)) {
		cout << "Found matching edge" << endl;
	}
	// Front Up
	else if ((Front[0][1] == col1 && Up[2][1] == col2) || (Front[0][1] == col2 && Up[2][1] == col1)) {
		cout << "Found matching edge" << endl;
	}
	// Right Up
	else if ((Right[0][1] == col1 && Up[1][2] == col2) || (Right[0][1] == col2 && Up[1][2] == col1)) {
		cout << "Found matching edge" << endl;
	}
	// Right Back
	else if ((Right[1][2] == col1 && Back[1][2] == col2) || (Right[1][2] == col2 && Back[1][2] == col1)) {
		cout << "Found matching edge" << endl;
		Rpr();
		U();
		R();
	}
	// Left Up
	else if ((Left[0][1] == col1 && Up[1][0] == col2) || (Left[0][1] == col2 && Up[1][0] == col1)) {
		cout << "Found matching edge" << endl;
	}
	// Left Back
	else if ((Left[1][0] == col1 && Back[1][0] == col2) || (Left[1][0] == col2 && Back[1][0] == col1)) {
		cout << "Found matching edge" << endl;
		L();
		Upr();
		Lpr();
		U();
	}
	// Back Up
	else if ((Back[0][1] == col1 && Up[0][1] == col2) || (Back[0][1] == col2 && Up[0][1] == col1)) {
		cout << "Found matching edge" << endl;
	}
	PlaceF2L();
}
void PlaceF2L() {
	cout << "Placing combination" << endl;
	// White is right
	if (Right[0][0] == 'W') {
		if (Front[1][1] == Front[0][2] && Front[1][1] == Front[1][2] && Right[1][1] == Right[1][0] && Right[1][1] == Up[2][2]) {
			L();
			Dpr();
			Lpr();
			U();
			L();
			D();
			Lpr();
		}
		if (Front[1][1] == Front[0][2] && Front[1][1] == Right[1][0] && Right[1][1] == Front[1][2] && Right[1][1] == Up[2][2]) {
			U();
			Fpr();
			Upr();
			F();
			Upr();
			R();
			U();
			Rpr();
		}
		if (Front[1][1] == Front[0][1] & Front[1][1] == Front[0][2] && Right[1][1] == Up[2][1] && Right[1][1] == Up[2][2]) {
			Upr();
			Fpr();
			U();
			F();
		}
		if (Front[1][1] == Up[2][1] && Front[1][1] == Front[0][2] && Right[1][1] == Front[0][1] && Right[1][1] == Up[2][2]) {
			Rpr();
			U();
			U();
			R();
			R();
			U();
			R();
			R();
			U();
			R();
		}
		if (Front[1][1] == Front[0][2] && Front[1][1] == Left[0][1] && Right[1][1] == Up[2][2] && Right[1][1] == Up[1][0]) {
			R();
			R();
			B();
			U();
			Bpr();
			Upr();
			R();
			R();
		}
		if (Front[1][1] == Front[0][2] && Front[1][1] == Up[1][0] && Right[1][1] == Up[2][2] && Right[1][1] == Left[0][1]) {
			Upr();
			R();
			U();
			Rpr();
			U();
			R();
			U();
			Rpr();
		}
		if (Front[1][1] == Front[0][2] && Front[1][1] == Up[0][1] && Right[1][1] == Up[2][2] && Right[1][1] == Back[0][1]) {
			R();
			U();
			Rpr();
		}
		if (Front[1][1] == Front[0][2] && Front[1][1] == Back[0][1] && Right[1][1] == Up[2][2] && Right[1][1] == Up[0][1]) {
			Bpr();
			Rpr();
			Upr();
			R();
			R();
			U();
			Rpr();
			B();
		}
		if (Front[1][1] == Front[0][2] && Front[1][1] == Up[1][2] && Right[1][1] == Up[2][2] && Right[1][1] == Right[0][1]) {
			Upr();
			R();
			Upr();
			Rpr();
			U();
			R();
			U();
			Rpr();
		}
		if (Front[1][1] == Front[0][2] && Front[1][1] == Right[0][1] && Right[1][1] == Up[2][2] && Right[1][1] == Up[1][2]) {
			R();
			Upr();
			B();
			Upr();
			Bpr();
			U();
			U();
			Rpr();
		}
	}
	// White is front
	if (Front[0][2] == 'W') {
		if (Front[1][1] == Front[1][2] && Front[1][1] == Up[2][2] && Right[1][1] == Right[0][0] && Right[1][1] == Right[1][0]) {
			Bpr();
			D();
			B();
			Upr();
			Bpr();
			Dpr();
			B();
		}
		if (Front[1][1] == Right[1][0] && Front[1][1] == Up[2][2] && Right[1][1] == Front[1][2] && Right[1][1] == Right[0][0]) {
			Upr();
			R();
			Bpr();
			R();
			B();
			Rpr();
			U();
			Rpr();
		}
		if (Front[1][1] == Front[0][1] && Front[1][1] == Up[2][2] && Right[1][1] == Up[2][1] && Right[1][1] == Right[0][0]) {
			U();
			Fpr();
			U();
			F();
			Upr();
			Fpr();
			Upr();
			F();
		}
		if (Front[1][1] == Up[2][1] && Front[1][1] == Up[2][2] && Right[1][1] == Front[0][1]  && Right[1][1] == Right[0][0]) {
			R();
			B();
			L();
			Upr();
			Lpr();
			Bpr();
			Rpr();
		}
		if (Front[1][1] == Up[2][2] && Front[1][1] == Left[0][1] && Right[1][1] == Right[0][0] && Right[1][1] == Up[1][0]) {
			Fpr();
			Upr();
			F();
		}
		if (Front[1][1] == Up[2][2] && Front[1][1] == Up[1][0] && Right[1][1] == Right[0][0] && Right[1][1] == Left[0][1]) {
			R();
			U();
			B();
			U();
			U();
			Bpr();
			U();
			Rpr();
		}
		if (Front[1][1] == Up[2][2] && Front[1][1] == Up[0][1] && Right[1][1] == Right[0][0] && Right[1][1] == Back[0][1]) {
			U();
			U();
			R();
			B();
			U();
			Bpr();
			U();
			U();
			Rpr();
		}
		if (Front[1][1] == Up[2][2] && Front[1][1] == Back[0][1] && Right[1][1] == Right[0][0] && Right[1][1] == Up[0][1]) {
			R();
			R();
			U();
			B();
			Upr();
			Bpr();
			R();
			R();
		}
		if (Front[1][1] == Up[2][2] && Front[1][1] == Up[1][2] && Right[1][1] == Right[0][0] && Right[1][1] == Right[0][1]) {
			U();
			R();
			Upr();
			Rpr();
		}
		if (Front[1][1] == Up[2][2] && Front[1][1] == Right[0][1] && Right[1][1] == Right[0][0] && Right[1][1] == Up[1][2]) {
			Fpr();
			U();
			Lpr();
			U();
			U();
			L();
			U();
			U();
			F();
		}
	}
	// White is up
	if (Up[2][2] == 'W') {
		if (Front[1][1] == Front[1][2] && Front[1][1] == Right[0][0] && Right[1][1] == Right[1][0] && Right[1][1] == Front[0][2]) {
			F();
			F();
			Upr();
			F();
			F();
			Upr();
			F();
			F();
			U();
			U();
			F();
			F();
		}
		if (Front[1][1] == Right[0][0] && Front[1][1] == Right[1][0] && Right[1][1] == Front[0][2] && Right[1][1] == Front[1][2]) {
			Fpr();
			U();
			F();
			R();
			U();
			U();
			Rpr();
		}
		if (Front[1][1] == Front[0][1] && Front[1][1] == Right[0][0] && Right[1][1] == Front[0][2] && Right[1][1] == Up[2][1]) {
			Fpr();
			U();
			U();
			F();
			U();
			Fpr();
			Upr();
			F();
		}
		if (Front[1][1] == Up[2][1] && Front[1][1] == Right[0][0] && Right[1][1] == Front[0][1] && Right[1][1] == Front[0][2]) {
			R();
			U();
			R();
			Bpr();
			Rpr();
			B();
			U();
			U();
			Rpr();
		}
		if (Front[1][1] == Right[0][0] && Front[1][1] == Left[0][1] && Right[1][1] == Front[0][2] && Right[1][1] == Up[1][0]) {
			Upr();
			Fpr();
			U();
			U();
			F();
			F();
			Rpr();
			Fpr();
			R();
		}
		if (Front[1][1] == Right[0][0] && Front[1][1] == Up[1][0] && Right[1][1] == Front[0][2] && Right[1][1] == Left[0][1]) {
			R();
			B();
			U();
			U();
			Bpr();
			Rpr();
		}
		if (Front[1][1] == Right[0][0] && Front[1][1] == Up[0][1] && Right[1][1] == Front[0][2] && Right[1][1] == Back[0][1]) {
			U();
			R();
			U();
			U();
			Rpr();
			U();
			R();
			Upr();
			Rpr();
		}
		if (Front[1][1] == Right[0][0] && Front[1][1] == Back[0][1] && Right[1][1] == Front[0][2] && Right[1][1] == Up[0][1]) {
			Fpr();
			Lpr();
			U();
			U();
			L();
			F();
		}
		if (Front[1][1] == Right[0][0] && Front[1][1] == Up[1][2] && Right[1][1] == Front[0][2] && Right[1][1] == Right[0][1]) {
			R();
			U();
			U();
			Rpr();
			Upr();
			R();
			U();
			Rpr();
		}
		if (Front[1][1] == Right[0][0] && Front[1][1] == Right[0][1] && Right[1][1] == Front[0][2] && Right[1][1] == Up[1][2]) {
			U();
			U();
			R();
			B();
			U();
			B();
			B();
			R();
			B();
			R();
			R();
		}
	}
}
//--------------------------------------------- Final Layer ---------------------------------------------------------||
// OLL
void YCross() {
	cout << "Solving Yellow Cross" << endl;
	if (Up[1][0] == 'Y' && Up[1][2] == 'Y' && Up[0][1] == 'Y' && Up[2][1] == 'Y') {
		cout << "Done" << endl;
	}
	// Line
	else if (Up[1][0] == 'Y' && Up[1][2] == 'Y') {
		F();

		R();
		U();
		Rpr();
		Upr();

		Fpr();
	}
	else if (Up[0][1] == 'Y' && Up[2][1] == 'Y') {
		U();

		F();
		R();
		U();
		Rpr();
		Upr();
		Fpr();
	}
	// "L"
	else if (Up[2][1] == 'Y' && Up[1][2] == 'Y') {
		B();

		U();
		L();
		Upr();
		Lpr();

		Bpr();
	}
	else if (Up[1][0] == 'Y' && Up[2][1] == 'Y') {
		Upr();
		B();

		U();
		L();
		Upr();
		Lpr();

		Bpr();
	}
	else if (Up[0][1] == 'Y' && Up[1][0] == 'Y') {
		Upr();
		Upr();
		B();

		U();
		L();
		Upr();
		Lpr();

		Bpr();
	}
	else if (Up[0][1] == 'Y' && Up[1][2] == 'Y') {
		U();
		B();

		U();
		L();
		Upr();
		Lpr();

		Bpr();
	}
	else {
		F();
		R();
		U();
		Rpr();
		Upr();
		Fpr();

		B();
		U();
		L();
		Upr();
		Lpr();
		Bpr();
	}
}
void YCorners() {
	//http://www.cubewhiz.com/2lookoll.php
	// goes through then turns if none work
	bool unsolved = 1;
	while (unsolved == 1) {
		if (Up[0][0] == 'Y' && Up[0][1] == 'Y' && Up[0][2] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Up[2][0] == 'Y' && Up[2][1] == 'Y' && Up[2][2] == 'Y') {
			unsolved = 0;
		}
		// #23
		if (Up[0][0] == 'Y' && Up[0][1] == 'Y' && Up[0][2] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Up[2][1] == 'Y' && Front[0][0] == 'Y' && Front[0][2] == 'Y') {
			Rpr();
			Rpr();
			D();

			Rpr();
			U();
			U();
			R();
			Dpr();
			Rpr();
			U();
			U();
			Rpr();
			unsolved = 0;
		}
		// #24
		else if (Up[0][0] == 'Y' && Up[0][1] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Up[2][0] == 'Y' && Up[2][1] == 'Y' && Front[0][2] == 'Y' && Back[0][2] == 'Y') {
			Rpr();
			Fpr();

			L();
			U();

			R();
			Fpr();

			Lpr();
			F();
			unsolved = 0;
		}
		// #25
		else if (Up[0][0] == 'Y' && Up[0][1] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Up[2][1] == 'Y' && Up[2][2] == 'Y' && Front[0][0] == 'Y' && Right[0][2] == 'Y') {
			Rpr();
			F();
			R();
			Bpr();
			Rpr();
			Fpr();
			R();
			B();
			unsolved = 0;
		}
		// #27
		else if (Up[0][1] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Up[2][0] == 'Y' && Up[2][1] == 'Y' && Back[0][0] == 'Y' && Right[0][2] == 'Y' && Front[0][2] == 'Y') {
			R();
			U();
			Rpr();
			U();
			R();
			U();
			U();
			Rpr();
			unsolved = 0;
		}
		// #26
		else if (Up[0][1] == 'Y' && Up[0][2] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Up[2][1] == 'Y' && Left[0][0] == 'Y' && Front[0][0] == 'Y' && Right[0][0] == 'Y') {
			R();
			U();
			U();

			Rpr();
			Upr();
			R();
			Upr();
			Rpr();
			unsolved = 0;
		}
		// #22
		else if (Up[0][1] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Up[2][1] == 'Y' && Left[0][0] == 'Y' && Left[0][2] == 'Y' && Front[0][2] == 'Y' && Back[0][2] == 'Y') {
			R();
			U();
			U();

			R();
			R();
			Upr();

			R();
			R();
			Upr();

			R();
			R();
			U();
			U();
			R();
			unsolved = 0;
		}
		// #21
		else if (Up[0][1] == 'Y' && Up[1][0] == 'Y' && Up[1][1] == 'Y' && Up[1][2] == 'Y' && Front[0][0] == 'Y' && Front[0][2] == 'Y' && Back[0][0] == 'Y' && Back[0][2] == 'Y') {
			R();
			U();
			U();

			Rpr();
			Upr();
			R();
			U();
			Rpr();
			Upr();
			R();
			Upr();
			Rpr();
			unsolved = 0;
		}
		else T();
	}
}
// PLL
void PLL() {
	// Corners
	cout << "Doing Corners \n";
	if (Front[0][0] == Front[0][2] && Right[0][0] == Right[0][2] && Back[0][0] == Back[0][2] && Left[0][0] == Left[0][2]) {}
	else if (Front[0][0] != Front[0][2] && Right[0][0] != Right[0][2] && Back[0][0] != Back[0][2] && Left[0][0] != Left[0][2]) {
		F();
		R();
		Upr();
		Rpr();
		Upr();
		R();
		U();
		Rpr();
		Fpr();

		R();
		U();
		Rpr();
		Upr();
		Rpr();
		F();
		R();
		Fpr();
	}
	else if (Front[0][0] == Front[0][2] || Right[0][0] == Right[0][2] || Back[0][0] == Back[0][2] || Left[0][0] == Left[0][2]) {
		if (Front[0][0] == Front[0][2]) {
			U();
		}
		else if (Right[0][0] == Right[0][2]) {
			U();
			U();
		}
		else if (Back[0][0] == Back[0][2]) {
			Upr();
		}
		R();
		U();
		Rpr();
		Upr();
		Rpr();
		F();
		R();
		R();
		Upr();
		Rpr();
		Upr();
		R();
		U();
		Rpr();
		Fpr();
	}
	if (Front[0][0] == Front[1][1]) {}
	else if (Front[0][0] == Right[1][1]) {
		Upr();
	}
	else if (Front[0][0] == Back[1][1]) {
		U();
		U();
	}
	else if (Front[0][0] == Left[1][1]) {
		U();
	}
	// Sides
	cout << "doing sides \n";
	// 3 edge cycle
	if ((Front[0][1] == Front[1][1] && Right[0][1] != Right[1][1] && Back[0][1] != Back[1][1] && Left[0][1] != Left[0][0]) || (Front[0][1] != Front[1][1] && Right[0][1] == Right[1][1] && Back[0][1] != Back[1][1] && Left[0][1] != Left[0][0]) || (Front[0][1] != Front[1][1] && Right[0][1] != Right[1][1] && Back[0][1] == Back[1][1] && Left[0][1] != Left[0][0]) || (Front[0][1] != Front[1][1] && Right[0][1] != Right[1][1] && Back[0][1] != Back[1][1] && Left[0][1] == Left[0][0])) {
		if (Front[0][1] == Front[1][1] && Right[0][1] != Right[1][1] && Back[0][1] != Back[1][1] && Left[0][1] != Left[0][0]) {
			T();
			T();
		}
		else if (Front[0][1] != Front[1][1] && Right[0][1] == Right[1][1] && Back[0][1] != Back[1][1] && Left[0][1] != Left[0][0]) {
			Tpr();
		}
		else if (Front[0][1] != Front[1][1] && Right[0][1] != Right[1][1] && Back[0][1] == Back[1][1] && Left[0][1] != Left[0][0]) {

		}
		else if (Front[0][1] != Front[1][1] && Right[0][1] != Right[1][1] && Back[0][1] != Back[1][1] && Left[0][1] == Left[0][0]) {
			T();
		}
		// Part 1
		cout << "doing part 1 \n";
		if (Front[0][1] == Right[1][1]) {
			R();
			Upr();
			R();
			U();
			R();
			U();
			R();
			Upr();
			Rpr();
			Upr();
			R();
			R();
		}
		else if (Front[0][1] == Left[1][1]) {
			Lpr();
			U();
			Lpr();
			Upr();
			Lpr();
			Upr();
			Lpr();
			U();
			L();
			U();
			L();
			L();
		}
	}
	// Opposite edge swap
	else if (Front[0][1] == Back[1][1] && Back[0][1] == Front[1][1] && Right[0][1] == Left[1][1] && Left[0][1] == Right[1][1]) {
		cout << "doing opposite edge swap";
		L();
		L();
		R();
		R();
		Bpr();
		L();
		L();
		R();
		R();
		U();
		U();
		L();
		L();
		R();
		R();
		Bpr();
		L();
		L();
		R();
		R(); 
	}
	// Adjacent edge swap
	else if (Front[0][1] == Right[1][1] && Right[0][1] == Front[1][1] && Left[0][1] == Back[1][1] && Back[0][1] == Left[1][1]) {
		U();
		Rpr();
		Upr();

		R();
		Upr();
		R();
		U();
		R();
		Upr();
		Rpr();
		U();
		R();
		U();

		R();
		R();
		Upr();
		Rpr();
		U();

		L();
		L();
		R();
		R();
		Bpr();
		L();
		L();
		R();
		R();
		U();
		U();
		L();
		L();
		R();
		R();
		Bpr();
		L();
		L();
		R();
		R();
	}
}


