#include "Cell.h"

//�����������
Cell::Cell() {
	state   = CLOSE;
	content = EMPTY;
}

//����������� �����������
Cell::Cell(const Cell &cell) {
	state   = cell.state;
	content = cell.content;
}

//���������� ��������� ������������
Cell &Cell::operator=(const Cell &cell) {
	state   = cell.state;
	content = cell.content;
	
	return *this;
}

//��������� state

//�������� �� ������ ��������
bool Cell::is_close() const {return state == CLOSE;}

//�������� �� ������ �� ��������
bool Cell::is_not_close() const {return not is_close();}

//�������� �� ������ ��������
bool Cell::is_open() const {return state == OPEN;}

//�������� �� ������ �� ��������
bool Cell::is_not_open() const {return not is_open();}

//�������� �� ������ ����������
bool Cell::is_mark() const {return state == MARK;}

//�������� �� ������ �� ����������
bool Cell::is_not_mark() const {return not is_mark();}

//���������� content

//���� �� � ������ ����
bool Cell::is_mine() const {return content == MINE;}

//��� �� � ������ ����
bool Cell::is_not_mine() const {return not is_mine();}

//�������� �� ������ ������
bool Cell::is_empty() const {return content == EMPTY;}

//�������� �� ������ �� ������
bool Cell::is_not_empty() const {return not is_empty();}

//���� �� � ������ ���������
bool Cell::is_hint() const {
	return HINT_1 <= content and content <= HINT_8;
}

//��� �� � ������ ���������
bool Cell::is_not_hint() const {return not is_hint();}

//��������� state

//������� ������ ��������
void Cell::open() {
	if (state == CLOSE) {
		state = OPEN;
	} else {
		cout << OPEN_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//������� ������ ����������
void Cell::mark() {
	if (state == CLOSE) {
		state = MARK;
	} else {
		cout << MARK_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//������� ������ ������������
void Cell::unmark() {
	if (state == MARK) {
		state = CLOSE;
	} else {
		cout << UNMARK_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//���������� content

//��������� ���� � ������
void Cell::mine() {
	if (state == CLOSE) {
		if (content == EMPTY) {
			content = MINE;
		} else {
			cout << MINE_ERROR_2 << endl;
			exit(EXIT_FAILURE);
		}
		
	} else {
		cout << MINE_ERROR_1 << endl;
		exit(EXIT_FAILURE);
	}
}

//��������� ��������� � ������/��������� �������� ���������
void Cell::hint_up() {
	if (state == CLOSE) {
		
		if (content == EMPTY or (content >= HINT_1 
		and content <= HINT_8)) {
			
			if (content < HINT_8) {
				content++;
			} else {
				cout << HINT_UP_ERROR_3 << endl;
				exit(EXIT_FAILURE);
			}
			
		} else {
			cout << HINT_UP_ERROR_2 << endl;
			exit(EXIT_FAILURE);
		}
		
	} else {
		cout << HINT_UP_ERROR_1 << endl;
		exit(EXIT_FAILURE);
	}
}

//��������� ��������� � ������/��������� �������� ���������
void Cell::hint_down() {
	if (state == CLOSE) {
		
		if (content == EMPTY or (content >= HINT_1 
		and content <= HINT_8)) {
			
			if (content > HINT_1) {
				content--;
			} else {
				cout << HINT_DOWN_ERROR_3 << endl;
				exit(EXIT_FAILURE);
			}
			
		} else {
			cout << HINT_DOWN_ERROR_2 << endl;
			exit(EXIT_FAILURE);
		}
		
	} else {
		cout << HINT_DOWN_ERROR_1 << endl;
		exit(EXIT_FAILURE);
	}
}

//�������� �������� ���������
int Cell::hint() const {
	if (HINT_1 <= content and content <= HINT_8) {
		return content;
	} else {
		cout << HINT_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//����� �����
void Cell::out() const {
	cout << "state: "   << state   << endl;
	cout << "content: " << content << endl;
}
