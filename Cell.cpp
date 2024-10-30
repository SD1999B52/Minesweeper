#include "Cell.h"

//конструктор
Cell::Cell() {
	state   = CLOSE;
	content = EMPTY;
}

//конструктор копировани€
Cell::Cell(const Cell &cell) {
	state   = cell.state;
	content = cell.content;
}

//перегрузка оператора присваивани€
Cell &Cell::operator=(const Cell &cell) {
	state   = cell.state;
	content = cell.content;
	
	return *this;
}

//состо€ние state

//€вл€етс€ ли €чейка закрытой
bool Cell::is_close() const {return state == CLOSE;}

//€вл€етс€ ли €чейка не закрытой
bool Cell::is_not_close() const {return not is_close();}

//€вл€етс€ ли €чейка открытой
bool Cell::is_open() const {return state == OPEN;}

//€вл€етс€ ли €чейка не открытой
bool Cell::is_not_open() const {return not is_open();}

//€вл€етс€ ли €чейка помеченной
bool Cell::is_mark() const {return state == MARK;}

//€вл€етс€ ли €чейка не помеченной
bool Cell::is_not_mark() const {return not is_mark();}

//содержание content

//есть ли в €чейке мина
bool Cell::is_mine() const {return content == MINE;}

//нет ли в €чейке мины
bool Cell::is_not_mine() const {return not is_mine();}

//€вл€етс€ ли €чейка пустой
bool Cell::is_empty() const {return content == EMPTY;}

//€вл€етс€ ли €чейка не пустой
bool Cell::is_not_empty() const {return not is_empty();}

//есть ли в €чейке подсказка
bool Cell::is_hint() const {
	return HINT_1 <= content and content <= HINT_8;
}

//нет ли в €чейке подсказки
bool Cell::is_not_hint() const {return not is_hint();}

//состо€ние state

//сделать €чейку открытой
void Cell::open() {
	if (state == CLOSE) {
		state = OPEN;
	} else {
		cout << OPEN_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//сделать €чейку отмеченной
void Cell::mark() {
	if (state == CLOSE) {
		state = MARK;
	} else {
		cout << MARK_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//сделать €чейку неотмеченной
void Cell::unmark() {
	if (state == MARK) {
		state = CLOSE;
	} else {
		cout << UNMARK_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//содержание content

//поместить мину в €чейку
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

//поместить подсказку в €чейку/увеличить значение подсказки
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

//поместить подсказку в €чейку/уменьшить значение подсказки
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

//получить значение подсказки
int Cell::hint() const {
	if (HINT_1 <= content and content <= HINT_8) {
		return content;
	} else {
		cout << HINT_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//вывод полей
void Cell::out() const {
	cout << "state: "   << state   << endl;
	cout << "content: " << content << endl;
}
