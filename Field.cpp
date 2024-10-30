#include "Field.h"

//������ �����������
Field::Field() {
	rows         = 0;
	columns      = 0;
	mines        = 0;
	cells        = 0;
	hints        = 0;
	empty        = 0;
	marked       = 0;
	opened_mines = 0;
	opened_hints = 0;
	opened_empty = 0;
	blocked      = true;
	
	map = new Cell *[0];
}

//�����������
Field::Field(int rows, int columns, int mines) {
	if ((rows >= 0) and (columns >= 0) and (mines >= 0)) {
		if ((rows * columns) > mines) {
			
			this->rows    = rows;
			this->columns = columns;
			this->mines   = mines;
			
			cells         = rows * columns;
			hints         = 0;
			marked        = 0;
			opened_mines  = 0;
			opened_hints  = 0;
			opened_empty  = 0;
			blocked       = false;
			
			map = new Cell *[rows];
			
			for (int i = 0; i < rows; i++) {
				map[i] = new Cell[columns];
			}
			
			srand(time(0));
			gen_mines();
			create_hints();
			
			empty         = cells - mines - hints;
			
		} else {
			cout << FIELD_ERROR_2 << endl;
			exit(EXIT_FAILURE);
		}
		
	} else {
		cout << FIELD_ERROR_1 << endl;
		exit(EXIT_FAILURE);
	}
}

//����������
Field::~Field() {
	for (int i = 0; i < rows; i++) {
		delete [] map[i];
	}
	
	delete [] map;
}

//����������� �����������
Field::Field(const Field &field) {copy_field(field);}

//���������� ��������� ������������
Field &Field::operator=(const Field &field) {
	copy_field(field);
	return *this;
}

//���������� �������� ���������� ���� � �������
void Field::copy_field(const Field &field) {
	
	//������� ������ map
	for (int i = 0; i < rows; i++) {
		delete [] map[i];
	}
	
	delete [] map;
	
	//��������� ������
	rows         = field.rows;
	columns      = field.columns;
	mines        = field.mines;
	cells        = field.cells;
	hints        = field.hints;
	empty        = field.empty;
	marked       = field.marked;
	opened_mines = field.opened_mines;
	opened_hints = field.opened_hints;
	opened_empty = field.opened_empty;
	blocked      = field.blocked;
	
	map = new Cell *[field.rows];
	
	for (int i = 0; i < field.rows; i++) {
		map[i] = new Cell[field.columns];
		
		for (int j = 0; j < field.columns; j++) {
			map[i][j] = field.map[i][j];
		}
	}
}

//�������� ���������� �����
int Field::num_rows() const {return rows;}

//�������� ���������� ��������
int Field::num_columns() const {return columns;}

//�������� ���������� ���
int Field::num_mines() const {return mines;}

//�������� ������������ ��������� ������
bool Field::check_coord(int row, int column) const {
	return 0 <= row and row < rows 
	and 0 <= column and column < columns;
}

//�������� ���������� ���������� �����
int Field::num_marked() const {return marked;}

//��������� ����� �� ��������� [min..max)
int Field::gen_number(int min, int max) const {
	return min + rand() % (max - min);
}

//��������� ���
void Field::gen_mines() {
	for (int i = 0; i < mines; i++) {
		
		while (true) {
			int column = gen_number(0, columns);
			int row    = gen_number(0, rows);
			
			if (map[row][column].is_not_mine()) {
				map[row][column].mine();
				break;
			}
		}
	}
}

//�������� ���������
void Field::create_hints() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			
			if (map[i][j].is_mine()) {
				
				for (int y = i - 1; y < i + 2; y++) {
					for (int x = j - 1; x < j + 2; x++) {
						
						if (check_coord(y, x)) {
							
							if (map[y][x].is_not_mine()) {
								
								//���� � ������ ��� �� ���� 
								//��������� (���� ���������)
								if (map[y][x].is_not_hint()) {
									hints++;
								}
								
								map[y][x].hint_up();
							}
						}
					}
				}
			}
		}
	}
}

//������������ � �������� �������� ������ �����
void Field::track_cells(int row, int column) {
	for (int y = row - 1; y < row + 2; y++) {
		for (int x = column - 1; x < column + 2; x++) {
			
			if (check_coord(y, x)) {
				
				if (map[y][x].is_close()) {
					map[y][x].open();
					
					if (map[y][x].is_hint()) {
						//���� �������� ���������
						opened_hints++;
					}
					
					if (map[y][x].is_empty()) {
						
						//���� �������� ������ �����
						opened_empty++;
						
						track_cells(y, x);
					}
				}
			}
		}
	}
}

//������� �� ���������� ������ � ������
void Field::open_mines() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (map[i][j].is_close() 
			and map[i][j].is_mine()) {
				map[i][j].open();
				opened_mines++;
			}
		}
	}
}

//�������� ��� ����
void Field::mark_mines() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (map[i][j].is_mine() 
			and map[i][j].is_not_mark()) {
				map[i][j].mark();
				marked++;
			}
		}
	}
}

//������� ������ ������ ��������� ���������
void Field::open_around(int row, int column) {
	int hint = map[row][column].hint();
	
	for (int y = row - 1; y < row + 2; y++) {
		for (int x = column - 1; x < column + 2; x++) {
			
			if (check_coord(y, x)) {
				
				if (map[y][x].is_close()) {
					
					if (map[y][x].is_hint()) {
						map[y][x].open();
						opened_hints++;
					}
					
					if (map[y][x].is_mine()) {
						map[y][x].open();
						opened_mines++;
					}
					
					if (map[y][x].is_empty()) {
						track_cells(y, x);
					}
				}
			}
		}
	}
}

//������� ������
void Field::open_cell(int row, int column) {
	if (check_coord(row, column)) {
		if (not blocked) {
			
			if (map[row][column].is_open()) {
				
				if (map[row][column].is_hint()) {
					open_around(row, column);
				}
			}
			
			if (map[row][column].is_close()) {
				
				if (map[row][column].is_mine()) {
					map[row][column].open();
					opened_mines++;
				}
				
				if (map[row][column].is_hint()) {
					map[row][column].open();
					opened_hints++;
				}
				
				if (map[row][column].is_empty()) {
					track_cells(row, column);
				}
			}
			
			if (is_victory()) {
				blocked = true;
				mark_mines();
			}
			
			if (is_defeat()) {
				blocked = true;
				open_mines();
			}
		}
		
	} else {
		cout << OPEN_CELL_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//�������� ������ ��� ����� �����
void Field::mark_cell(int row, int column) {
	if (check_coord(row, column)) {
		if (not blocked) {
			
			if (map[row][column].is_mark()) {
				map[row][column].unmark();
				marked--;
				return;
			}
			
			if (map[row][column].is_close()) {
				map[row][column].mark();
				marked++;
			}
		}
		
	} else {
		cout << MARK_CELL_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//��������� ������ �� ����
bool Field::is_victory() const {
	return opened_mines == 0 and opened_hints == hints 
	and opened_empty == empty;
}

//��������� �������� �� ����
bool Field::is_defeat() const {return opened_mines > 0;}

//�������� ������
const Cell &Field::cell(int row, int column) {
	if (check_coord(row, column)) {
		return map[row][column];
	} else {
		cout << CELL_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//����� ����� ����
void Field::out() const {
	cout << "rows: "         << rows         << endl;
	cout << "columns: "      << columns      << endl;
	cout << "mines: "        << mines        << endl;
	cout << "cells: "        << cells        << endl;
	cout << "hints: "        << hints        << endl;
	cout << "empty: "        << empty        << endl;
	cout << "marked: "       << marked       << endl;
	cout << "opened_mines: " << opened_mines << endl;
	cout << "opened_hints: " << opened_hints << endl;
	cout << "opened_empty: " << opened_empty << endl;
	cout << "blocked: "      << blocked      << endl;
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << endl;
			cout << "[" << i << "]";
			cout << "[" << j << "]";
			cout << endl;
			
			map[i][j].out();
		}
	}
}
