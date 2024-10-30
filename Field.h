#include "Cell.h"

#include <ctime>

#define FIELD_ERROR_1   "Field::Field: The number of rows, columns, mines cannot be negative."
#define FIELD_ERROR_2   "Field::Field: There are more mines than cells."
#define OPEN_CELL_ERROR "Field::open_cell: The requested cell does not exist."
#define MARK_CELL_ERROR "Field::mark_cell: The requested cell does not exist."
#define CELL_ERROR      "Field::cell: The requested cell does not exist."

class Field {
	
	private:
		
		int rows; //количество строк
		int columns; //количество столбцов
		int mines; //количество мин
		int cells; //количество ячеек
		int hints; //количество подсказок
		int empty; //количество пустых ячеек
		int marked; //количество отмеченных ячеек
		int opened_mines; //количество открытых мин
		int opened_hints; //количество открытых подсказок
		int opened_empty; //количество открытых пустых ячеек
		bool blocked; //блокировка поля да/нет
		Cell **map; //игровое поле
		
		int gen_number(int min, int max) const; //генерация числа из диапазона [min..max)
		void gen_mines(); //генерация мин
		void create_hints(); //создание подсказок
		void track_cells(int row, int column); //отслеживание и открытие соседних пустых ячеек
		void open_mines(); //открыть не отмеченные ячейки с минами
		void mark_mines(); //отметить все мины
		void copy_field(const Field &field); //копировать значения указанного поля в текущее
		void open_around(int row, int column); //открыть ячейки вокруг указанной подсказки
		
	public:
		
		Field(); //пустой конструктор
		Field(int rows, int columns, int mines); //конструктор
		~Field(); //деструктор
		Field(const Field &field); //конструктор копирования
		Field &operator=(const Field &field); //перегрузка оператора присваивания
		
		bool check_coord(int row, int column) const; //проверка правильности координат ячейки
		
		int num_rows() const; //получить количество строк
		int num_columns() const; //получить количество столбцов
		int num_mines() const; //получить количество мин
		int num_marked() const; //получить количество помеченных ячеек
		
		const Cell &cell(int row, int column); //получить ячейку
		
		void open_cell(int row, int column); //открыть ячейку
		void mark_cell(int row, int column); //пометить ячейку или снять метку
		
		bool is_victory() const; //проверить победу на поле
		bool is_defeat() const; //проверить поражние на поле
		
		void out() const; //вывод полей поля
};
