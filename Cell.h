#include <iostream>
#include <stdlib.h>

#define OPEN_ERROR        "Cell::open: The cell must be closed and unmarked."
#define MARK_ERROR        "Cell::mark: The cell must be closed."
#define UNMARK_ERROR      "Cell::mark: The cell must be marked."
#define MINE_ERROR_1      "Cell::mine: The cell must be closed and unmarked."
#define MINE_ERROR_2      "Cell::mine: The cell must be empty."
#define HINT_UP_ERROR_1   "Cell::hint_up: The cell must be closed and unmarked."
#define HINT_UP_ERROR_2   "Cell::hint_up: The cell must be empty or be a hint."
#define HINT_UP_ERROR_3   "Cell::hint_up: The hint value cannot be more than 8."
#define HINT_DOWN_ERROR_1 "Cell::hint_down: The cell must be closed and unmarked."
#define HINT_DOWN_ERROR_2 "Cell::hint_down: The cell must be empty or be a hint"
#define HINT_DOWN_ERROR_3 "Cell::hint_down: The hint value cannot be less than 1."
#define HINT_ERROR        "Cell::hint: The cell is not a hint."

using namespace std;

class Cell {
	
	private:
		
		int state; //состо€ние €чейки
		int content; //содержание €чейки
		
	public:
		
		//состо€ние state
		static const int CLOSE  = 0;
		static const int OPEN   = 1;
		static const int MARK   = 2;
		
		//содержание content
		static const int EMPTY  = 0;
		static const int HINT_1 = 1;
		static const int HINT_2 = 2;
		static const int HINT_3 = 3;
		static const int HINT_4 = 4;
		static const int HINT_5 = 5;
		static const int HINT_6 = 6;
		static const int HINT_7 = 7;
		static const int HINT_8 = 8;
		static const int MINE   = 9;
		
		Cell(); //конструктор
		Cell(const Cell &cell); //конструктор копировани€
		Cell &operator=(const Cell &cell); //перегрузка оператора присваивани€
		
		//состо€ние state
		bool is_close() const; //€вл€етс€ ли €чейка закрытой
		bool is_not_close() const; //€вл€етс€ ли €чейка не закрытой
		bool is_open() const; //€вл€етс€ ли €чейка открытой
		bool is_not_open() const; //€вл€етс€ ли €чейка не открытой
		bool is_mark() const; //€вл€етс€ ли €чейка помеченной
		bool is_not_mark() const; //€вл€етс€ ли €чейка не помеченной
		
		//содержание content
		bool is_mine() const; //есть ли в €чейке мина
		bool is_not_mine() const; //нет ли в €чейке мины
		bool is_empty() const; //€вл€етс€ ли €чейка пустой
		bool is_not_empty() const; //€вл€етс€ ли €чейка не пустой
		bool is_hint() const; //есть ли в €чейке подсказка
		bool is_not_hint() const; //нет ли в €чейке подсказки
		
		//состо€ние state
		void open(); //сделать €чейку открытой
		
		void mark(); //сделать €чейку отмеченной
		void unmark(); //сделать €чейку неотмеченной
		
		//содержание content
		void mine(); //поместить мину в €чейку
		
		void hint_up(); //поместить подсказку в €чейку/увеличить значение подсказки
		void hint_down(); //поместить подсказку в €чейку/уменьшить значение подсказки
		int hint() const; //получить значение подсказки
		
		void out() const; //вывод полей €чейки
};
