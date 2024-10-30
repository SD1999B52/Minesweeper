#include "Cell.h"

#include <ctime>

#define FIELD_ERROR_1   "Field::Field: The number of rows, columns, mines cannot be negative."
#define FIELD_ERROR_2   "Field::Field: There are more mines than cells."
#define OPEN_CELL_ERROR "Field::open_cell: The requested cell does not exist."
#define MARK_CELL_ERROR "Field::mark_cell: The requested cell does not exist."
#define CELL_ERROR      "Field::cell: The requested cell does not exist."

class Field {
	
	private:
		
		int rows; //���������� �����
		int columns; //���������� ��������
		int mines; //���������� ���
		int cells; //���������� �����
		int hints; //���������� ���������
		int empty; //���������� ������ �����
		int marked; //���������� ���������� �����
		int opened_mines; //���������� �������� ���
		int opened_hints; //���������� �������� ���������
		int opened_empty; //���������� �������� ������ �����
		bool blocked; //���������� ���� ��/���
		Cell **map; //������� ����
		
		int gen_number(int min, int max) const; //��������� ����� �� ��������� [min..max)
		void gen_mines(); //��������� ���
		void create_hints(); //�������� ���������
		void track_cells(int row, int column); //������������ � �������� �������� ������ �����
		void open_mines(); //������� �� ���������� ������ � ������
		void mark_mines(); //�������� ��� ����
		void copy_field(const Field &field); //���������� �������� ���������� ���� � �������
		void open_around(int row, int column); //������� ������ ������ ��������� ���������
		
	public:
		
		Field(); //������ �����������
		Field(int rows, int columns, int mines); //�����������
		~Field(); //����������
		Field(const Field &field); //����������� �����������
		Field &operator=(const Field &field); //���������� ��������� ������������
		
		bool check_coord(int row, int column) const; //�������� ������������ ��������� ������
		
		int num_rows() const; //�������� ���������� �����
		int num_columns() const; //�������� ���������� ��������
		int num_mines() const; //�������� ���������� ���
		int num_marked() const; //�������� ���������� ���������� �����
		
		const Cell &cell(int row, int column); //�������� ������
		
		void open_cell(int row, int column); //������� ������
		void mark_cell(int row, int column); //�������� ������ ��� ����� �����
		
		bool is_victory() const; //��������� ������ �� ����
		bool is_defeat() const; //��������� �������� �� ����
		
		void out() const; //����� ����� ����
};
