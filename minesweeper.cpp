#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//размеры матрицы
const int ROWS = 10, COLUMNS = 20;

//количество бомб
const int BOMBS = 20;

//карта бомб
int labelA[ROWS][COLUMNS];

//вывод уровня
void out(int label[ROWS][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			cout << label[i][j];
		}
		
		cout << endl;
	}
}

//очистка уровня
void cls(int label[ROWS][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			label[i][j] = 0;
		}
	}
}

//генерация чилел в диапазоне
int rand(int min, int max) {
	return rand() % (max - min + 1) + min;
}

//генерация бомб
void gen(int label[ROWS][COLUMNS]) {
	
	srand(time(0));
	
	for (int i = 0; i < BOMBS; i++) {
		for (int j = 0; j < 1000; j++) {
			
			int x = rand(0, COLUMNS - 1);
			int y = rand(0, ROWS    - 1);
			
			if (label[y][x] == 0) {
				
				label[y][x] = 1;
				
				break;
			}
		}
	}
}

int main(int argc, char** argv) {
	
	gen(labelA);
	out(labelA);
	
	return 0;
}
