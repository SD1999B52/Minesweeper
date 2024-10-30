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
		
		int state; //��������� ������
		int content; //���������� ������
		
	public:
		
		//��������� state
		static const int CLOSE  = 0;
		static const int OPEN   = 1;
		static const int MARK   = 2;
		
		//���������� content
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
		
		Cell(); //�����������
		Cell(const Cell &cell); //����������� �����������
		Cell &operator=(const Cell &cell); //���������� ��������� ������������
		
		//��������� state
		bool is_close() const; //�������� �� ������ ��������
		bool is_not_close() const; //�������� �� ������ �� ��������
		bool is_open() const; //�������� �� ������ ��������
		bool is_not_open() const; //�������� �� ������ �� ��������
		bool is_mark() const; //�������� �� ������ ����������
		bool is_not_mark() const; //�������� �� ������ �� ����������
		
		//���������� content
		bool is_mine() const; //���� �� � ������ ����
		bool is_not_mine() const; //��� �� � ������ ����
		bool is_empty() const; //�������� �� ������ ������
		bool is_not_empty() const; //�������� �� ������ �� ������
		bool is_hint() const; //���� �� � ������ ���������
		bool is_not_hint() const; //��� �� � ������ ���������
		
		//��������� state
		void open(); //������� ������ ��������
		
		void mark(); //������� ������ ����������
		void unmark(); //������� ������ ������������
		
		//���������� content
		void mine(); //��������� ���� � ������
		
		void hint_up(); //��������� ��������� � ������/��������� �������� ���������
		void hint_down(); //��������� ��������� � ������/��������� �������� ���������
		int hint() const; //�������� �������� ���������
		
		void out() const; //����� ����� ������
};
