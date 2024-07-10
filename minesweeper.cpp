#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//������� �������
const int ROWS = 10, COLUMNS = 20;

//���������� ����
const int BOMBS = 20;

//����� ����
int labelA[ROWS][COLUMNS];

//����� ������
void out(int label[ROWS][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			cout << label[i][j];
		}
		
		cout << endl;
	}
}

//������� ������
void cls(int label[ROWS][COLUMNS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			label[i][j] = 0;
		}
	}
}

//��������� ����� � ���������
int rand(int min, int max) {
	return rand() % (max - min + 1) + min;
}

//��������� ����
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
