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
		
		SDL_Texture *menu_texture; //меню
		SDL_Texture *pointer_texture; //указатель
		SDL_Texture *empty_texture; //пустая ячейка
		SDL_Texture *close_texture; //закрытая ячейка
		SDL_Texture *mine_texture; //мина
		SDL_Texture *mark_texture; //метка
		SDL_Texture *line_texture; //строка
		SDL_Texture *separator_texture; //разделитель
		SDL_Texture *back_texture; //кнопка "Назад"
		
		SDL_Texture *number_texture[10]; //числа
		
		int game_location; //меню или игра
		int menu_position; //пункт меню
		
		/*
		Новичек:      9x9     10 мин
		Любитель:     16x16   40 мин
		Профессионал: 16x30   99 мин
		*/
		
		Field field;
		
		int general_width; //общая ширина
		int general_height; //общая высота
		int field_height; //высота поля
		int line_height; //высота строки
		int field_y_offset; //отступ по Y для поля
		int general_x_offset; //общий отступ по X
		int general_y_offset; //общий отступ по Y
		
		int back_x0; //координата x0 кнопки "Назад"
		int back_x1; //координата x1 кнопки "Назад"
		int back_y0; //координата y0 кнопки "Назад"
		int back_y1; //координата y1 кнопки "Назад"
		
		void recalc_param(); //пересчитать размеры и отступы
		
		void draw_empty(int x, int y); //рисовать пустую ячейку
		void draw_close(int x, int y); //рисовать закрытую ячейку
		void draw_mark(int x, int y); //рисовать метку
		void draw_mine(int x, int y); //рисовать мину
		void draw_hint(int x, int y, int value); //рисовать ячейку с подсказкой
		void draw_digit(int x, int y, int value); //рисовать цифру
		void draw_separator(int x, int y); //рисовать разделитель
		void draw_back(int x, int y); //рисовать кнопку "Назад"
		
		int num_digits(int value) const; //получить количество цифр в числе
		int get_digit(int value, int index) const; //получить цифру из числа
		
		int x_to_column(int x) const; //перевести координату X окна в координату столбца
		int y_to_row(int y) const; //перевести координату Y окна в координату строки
		
		void draw_menu(); //рисовать меню
		void draw_game(); //рисовать игру
		
		bool check_coord(int x, int y); //проверка правильности координат окна
		
	public:
		
		static const int WINDOW_WIDTH          = 800;
		static const int WINDOW_HEIGHT         = 600;
		static const int CELL_SIZE             = 25;
		static const int POINTER_SIZE          = 25;
		static const int BACK_SIZE             = 25;
		
		static const int LOCATION_MENU         = 0;
		static const int LOCATION_GAME         = 1;
		
		static const int POSITION_RECRUIT      = 0; //"Новичек"
		static const int POSITION_AMATEUR      = 1; //"Любитель"
		static const int POSITION_PROFESSIONAL = 2; //"Профессионал"
		
		Window(); //конструктор
		~Window(); //деструктор
		
		void right_click(int x, int y); //правый клик мыши
		void left_click(int x, int y); //левый клик мыши
		void move_mouse(int x, int y); //перемещение мыши
		void redraw(); //перерисовать окно
};
