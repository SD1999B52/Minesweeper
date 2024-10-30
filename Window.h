#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

#include "Field.h"

#define WINDOW_ERROR_1    "Window::Window: Error creating the window."
#define WINDOW_ERROR_2    "Window::Window: Error creating the renderer or connecting it to the window."
#define WINDOW_ERROR_3    "Window::Window: The menu texture is not loaded."
#define WINDOW_ERROR_4    "Window::Window: The pointer texture is not loaded."
#define WINDOW_ERROR_5    "Window::Window: The texture of an empty cell is not loaded."
#define WINDOW_ERROR_6    "Window::Window: The texture of the closed cell is not loaded."
#define WINDOW_ERROR_7    "Window::Window: The texture of the mine is not loaded."
#define WINDOW_ERROR_8    "Window::Window: The texture of the marked cell is not loaded."
#define WINDOW_ERROR_9    "Window::Window: The line texture is not loaded."
#define WINDOW_ERROR_10   "Window::Window: The separator texture is not loaded."
#define WINDOW_ERROR_11   "Window::Window: The button texture is not loaded."
#define WINDOW_ERROR_12   "Window::Window: The textures of the cells with hints are not loaded."
#define MOVE_MOUSE_ERROR  "Window::move_mouse: The specified coordinates are outside the window."
#define LEFT_CLICK_ERROR  "Window::left_click: The specified coordinates are outside the window."
#define RIGHT_CLICK_ERROR "Window::right_click: The specified coordinates are outside the window."

class Window {
	
	private:
		
		SDL_Window *window;
		SDL_Renderer *renderer;
		
		SDL_Texture *menu_texture; //����
		SDL_Texture *pointer_texture; //���������
		SDL_Texture *empty_texture; //������ ������
		SDL_Texture *close_texture; //�������� ������
		SDL_Texture *mine_texture; //����
		SDL_Texture *mark_texture; //�����
		SDL_Texture *line_texture; //������
		SDL_Texture *separator_texture; //�����������
		SDL_Texture *back_texture; //������ "�����"
		
		SDL_Texture *number_texture[10]; //�����
		
		int game_location; //���� ��� ����
		int menu_position; //����� ����
		
		/*
		�������:      9x9     10 ���
		��������:     16x16   40 ���
		������������: 16x30   99 ���
		*/
		
		Field field;
		
		int general_width; //����� ������
		int general_height; //����� ������
		int field_height; //������ ����
		int line_height; //������ ������
		int field_y_offset; //������ �� Y ��� ����
		int general_x_offset; //����� ������ �� X
		int general_y_offset; //����� ������ �� Y
		
		int back_x0; //���������� x0 ������ "�����"
		int back_x1; //���������� x1 ������ "�����"
		int back_y0; //���������� y0 ������ "�����"
		int back_y1; //���������� y1 ������ "�����"
		
		void recalc_param(); //����������� ������� � �������
		
		void draw_empty(int x, int y); //�������� ������ ������
		void draw_close(int x, int y); //�������� �������� ������
		void draw_mark(int x, int y); //�������� �����
		void draw_mine(int x, int y); //�������� ����
		void draw_hint(int x, int y, int value); //�������� ������ � ����������
		void draw_digit(int x, int y, int value); //�������� �����
		void draw_separator(int x, int y); //�������� �����������
		void draw_back(int x, int y); //�������� ������ "�����"
		
		int num_digits(int value) const; //�������� ���������� ���� � �����
		int get_digit(int value, int index) const; //�������� ����� �� �����
		
		int x_to_column(int x) const; //��������� ���������� X ���� � ���������� �������
		int y_to_row(int y) const; //��������� ���������� Y ���� � ���������� ������
		
		void draw_menu(); //�������� ����
		void draw_game(); //�������� ����
		
		bool check_coord(int x, int y); //�������� ������������ ��������� ����
		
	public:
		
		static const int WINDOW_WIDTH          = 800;
		static const int WINDOW_HEIGHT         = 600;
		static const int CELL_SIZE             = 25;
		static const int POINTER_SIZE          = 25;
		static const int BACK_SIZE             = 25;
		
		static const int LOCATION_MENU         = 0;
		static const int LOCATION_GAME         = 1;
		
		static const int POSITION_RECRUIT      = 0; //"�������"
		static const int POSITION_AMATEUR      = 1; //"��������"
		static const int POSITION_PROFESSIONAL = 2; //"������������"
		
		Window(); //�����������
		~Window(); //����������
		
		void right_click(int x, int y); //������ ���� ����
		void left_click(int x, int y); //����� ���� ����
		void move_mouse(int x, int y); //����������� ����
		void redraw(); //������������ ����
};
