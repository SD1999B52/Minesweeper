#include "Window.h"

//конструктор
Window::Window() {
	window = SDL_CreateWindow(
		"Minesweeper", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, 
		WINDOW_HEIGHT, 0
	);
	if (window == NULL) {
		cout << WINDOW_ERROR_1 << endl;
		exit(EXIT_FAILURE);
	}
	
	renderer = SDL_CreateRenderer(window, -1, 
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		cout << WINDOW_ERROR_2 << endl;
		exit(EXIT_FAILURE);
	}
	
	menu_texture = IMG_LoadTexture(renderer, 
	"image/menu.png");
	if (menu_texture == NULL) {
		cout << WINDOW_ERROR_3 << endl;
		exit(EXIT_FAILURE);
	}
	
	pointer_texture = IMG_LoadTexture(renderer, 
	"image/pointer.png");
	if (pointer_texture == NULL) {
		cout << WINDOW_ERROR_4 << endl;
		exit(EXIT_FAILURE);
	}
	
	empty_texture = IMG_LoadTexture(renderer, 
	"image/empty.png");
	if (empty_texture == NULL) {
		cout << WINDOW_ERROR_5 << endl;
		exit(EXIT_FAILURE);
	}
	
	close_texture = IMG_LoadTexture(renderer, 
	"image/close.png");
	if (close_texture == NULL) {
		cout << WINDOW_ERROR_6 << endl;
		exit(EXIT_FAILURE);
	}
	
	mine_texture = IMG_LoadTexture(renderer, 
	"image/mine.png");
	if (mine_texture == NULL) {
		cout << WINDOW_ERROR_7 << endl;
		exit(EXIT_FAILURE);
	}
	
	mark_texture = IMG_LoadTexture(renderer, 
	"image/mark.png");
	if (mark_texture == NULL) {
		cout << WINDOW_ERROR_8 << endl;
		exit(EXIT_FAILURE);
	}
	
	line_texture = IMG_LoadTexture(renderer, 
	"image/line.png");
	if (line_texture == NULL) {
		cout << WINDOW_ERROR_9 << endl;
		exit(EXIT_FAILURE);
	}
	
	separator_texture = IMG_LoadTexture(renderer, 
	"image/separator.png");
	if (separator_texture == NULL) {
		cout << WINDOW_ERROR_10 << endl;
		exit(EXIT_FAILURE);
	}
	
	back_texture = IMG_LoadTexture(renderer, 
	"image/back.png");
	if (back_texture == NULL) {
		cout << WINDOW_ERROR_11 << endl;
		exit(EXIT_FAILURE);
	}
	
	char path[] = "image/number_ .png";
	
	for (int i = 0; i < 10; i++) {
		
		path[13] = char(i + 48);
		
		number_texture[i] = IMG_LoadTexture(
		renderer, path);
		if (number_texture[i] == NULL) {
			cout << WINDOW_ERROR_12 << endl;
			exit(EXIT_FAILURE);
		}
	}
	
	game_location = LOCATION_MENU;
	menu_position = POSITION_RECRUIT;
	
	draw_menu();
	
	SDL_RenderPresent(renderer);
}

//деструктор
Window::~Window() {
	if (menu_texture != NULL) {
		SDL_DestroyTexture(menu_texture);
	}
	
	if (pointer_texture != NULL) {
		SDL_DestroyTexture(pointer_texture);
	}
	
	if (empty_texture != NULL) {
		SDL_DestroyTexture(empty_texture);
	}
	
	if (close_texture != NULL) {
		SDL_DestroyTexture(close_texture);
	}
	
	if (mine_texture != NULL) {
		SDL_DestroyTexture(mine_texture);
	}
	
	if (mark_texture != NULL) {
		SDL_DestroyTexture(mark_texture);
	}
	
	if (line_texture != NULL) {
		SDL_DestroyTexture(line_texture);
	}
	
	if (separator_texture != NULL) {
		SDL_DestroyTexture(separator_texture);
	}
	
	if (back_texture != NULL) {
		SDL_DestroyTexture(back_texture);
	}
	
	for (int i = 0; i < 10; i++) {
		if (number_texture[i] != NULL) {
			SDL_DestroyTexture(number_texture[i]);
		}
	}
	
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	
	if (window != NULL) {
		SDL_DestroyWindow(window);
	}
}

//пересчитать размеры и отступы
void Window::recalc_param() {
	general_width    = CELL_SIZE * field.num_columns();
	line_height      = CELL_SIZE;
	field_height     = CELL_SIZE * field.num_rows();
	general_height   = field_height + line_height;
	general_x_offset = (WINDOW_WIDTH - general_width) / 2;
	general_y_offset = (WINDOW_HEIGHT - general_height) / 2;
	field_y_offset   = general_y_offset + CELL_SIZE;
	back_x0          = general_x_offset;
	back_x1          = general_x_offset + CELL_SIZE;
	back_y0          = general_y_offset;
	back_y1          = general_y_offset + CELL_SIZE;
}

//рисовать пустую €чейку
void Window::draw_empty(int x, int y) {
	SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(renderer, empty_texture, NULL, &rect);
}

//рисовать закрытую €чейку
void Window::draw_close(int x, int y) {
	SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(renderer, close_texture, NULL, &rect);
}

//рисовать метку
void Window::draw_mark(int x, int y) {
	SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(renderer, close_texture, NULL, &rect);
	SDL_RenderCopy(renderer, mark_texture, NULL, &rect);
}

//рисовать мину
void Window::draw_mine(int x, int y) {
	SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(renderer, empty_texture, NULL, &rect);
	SDL_RenderCopy(renderer, mine_texture, NULL, &rect);
}

//рисовать €чейку с подсказкой
void Window::draw_hint(int x, int y, int value) {
	SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(renderer, empty_texture, NULL, &rect);
	SDL_RenderCopy(renderer, number_texture[value], NULL, 
	&rect);
}

//рисовать цифру
void Window::draw_digit(int x, int y, int value) {
	SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(renderer, line_texture, NULL, &rect);
	SDL_RenderCopy(renderer, number_texture[value], NULL, 
	&rect);
}

//рисовать разделитель
void Window::draw_separator(int x, int y) {
	SDL_Rect rect = {x, y, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(renderer, line_texture, NULL, &rect);
	SDL_RenderCopy(renderer, separator_texture, NULL, &rect);
}

//рисовать кнопку "Ќазад"
void Window::draw_back(int x, int y) {
	SDL_Rect back_rect = {x, y, BACK_SIZE, BACK_SIZE};
	SDL_RenderCopy(renderer, back_texture, NULL, &back_rect);
}

//получить количество цифр в числе
int Window::num_digits(int value) const {
	int count = 1;
	
	while (value /= 10) {count++;}
	
	return count;
}

//получить цифру из числа
int Window::get_digit(int value, int index) const {
	int ten = 1;
	
	while (ten <= value / 10) {ten *= 10;}
	
	for (int i = 0; i < index; i++) {
		value %= ten;
		ten   /= 10;
	}
	
	return value / ten;
}

//перевести координату X окна в координату столбца
int Window::x_to_column(int x) const {
	return floor((x - general_x_offset) / (float)CELL_SIZE);
}

//перевести координату Y окна в координату строки
int Window::y_to_row(int y) const {
	return floor((y - field_y_offset) / (float)CELL_SIZE);
}

//рисовать меню
void Window::draw_menu() {
	SDL_Rect menu_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_RenderCopy(renderer, menu_texture, NULL, &menu_rect);
	
	int x, y;
	
	switch (menu_position) {
		
		case POSITION_RECRUIT:
			x = 175;
			y = 175;
			break;
		
		case POSITION_AMATEUR:
			x = 175;
			y = 200;
			break;
		
		case POSITION_PROFESSIONAL:
			x = 175;
			y = 225;
	}
	
	SDL_Rect pointer_rect = {x, y, POINTER_SIZE, POINTER_SIZE};
	SDL_RenderCopy(renderer, pointer_texture, NULL, &pointer_rect);
}

//рисовать игру
void Window::draw_game() {
	
	//вывод кнопки
	draw_back(general_x_offset, general_y_offset);
	
	//вывод надписи
	int marked_length = num_digits(field.num_marked());
	int mines_length  = num_digits(field.num_mines());
	
	int index = 1;
	
	int y = general_y_offset;
	
	for (int i = 0; i < marked_length; i++) {
		draw_digit(index * CELL_SIZE + general_x_offset, y, 
		get_digit(field.num_marked(), i));
		index++;
	}
	
	draw_separator(index * CELL_SIZE + general_x_offset, y);
	index++;
	
	for (int i = 0; i < mines_length; i++) {
		draw_digit(index * CELL_SIZE + general_x_offset, y, 
		get_digit(field.num_mines(), i));
		index++;
	}
	
	//вывод пол€
	for (int i = 0; i < field.num_rows(); i++) {
		for (int j = 0; j < field.num_columns(); j++) {
			
			int x = j * CELL_SIZE + general_x_offset;
			int y = i * CELL_SIZE + field_y_offset;
			
			if (field.cell(i, j).is_mark()) {
				draw_mark(x, y);
			}
			
			if (field.cell(i, j).is_close()) {
				draw_close(x, y);
			}
			
			if (field.cell(i, j).is_open()) {
				
				if (field.cell(i, j).is_empty()) {
					draw_empty(x, y);
				}
				
				if (field.cell(i, j).is_mine()) {
					draw_mine(x, y);
				}
				
				if (field.cell(i, j).is_hint()) {
					draw_hint(x, y, field.cell(i, j).hint());
				}
			}
		}
	}
}

//перерисовать окно
void Window::redraw() {
	SDL_RenderClear(renderer);
	
	if (game_location == LOCATION_MENU) {draw_menu();}
	if (game_location == LOCATION_GAME) {draw_game();}
	
	SDL_RenderPresent(renderer);
}

//проверка правильности координат окна
bool Window::check_coord(int x, int y) {
	return x >= 0 and x < WINDOW_WIDTH 
	and y >= 0 and y < WINDOW_HEIGHT;
}

//правый клик мыши
void Window::right_click(int x, int y) {
	if (check_coord(x, y)) {
		
		if (game_location == LOCATION_GAME) {
			
			int column = x_to_column(x);
			int row    = y_to_row(y);
			
			if (field.check_coord(row, column)) {
				field.mark_cell(row, column);
			}
		}
		
	} else {
		cout << RIGHT_CLICK_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//левый клик мыши
void Window::left_click(int x, int y) {
	if (check_coord(x, y)) {
		
		if (game_location == LOCATION_GAME) {
			
			int column = x_to_column(x);
			int row    = y_to_row(y);
			
			if (field.check_coord(row, column)) {
				field.open_cell(row, column);
			}
			
			if (x > back_x0 and x < back_x1 
			and y > back_y0 and y < back_y1) {
				game_location = LOCATION_MENU;
				return;
			}
		}
		
		if (game_location == LOCATION_MENU) {
			
			if (y > 175 and y < 200) {
				game_location = LOCATION_GAME;
				field         = Field(9, 9, 10);
				recalc_param();
			}
			
			if (y > 200 and y < 225) {
				game_location = LOCATION_GAME;
				field         = Field(16, 16, 40);
				recalc_param();
			}
			
			if (y > 225 and y < 250) {
				game_location = LOCATION_GAME;
				field         = Field(16, 30, 99);
				recalc_param();
			}
		}
		
	} else {
		cout << LEFT_CLICK_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}

//перемещение мыши
void Window::move_mouse(int x, int y) {
	if (check_coord(x, y)) {
		
		if (game_location == LOCATION_MENU) {
			
			if (y > 175 and y < 200) {
				menu_position = POSITION_RECRUIT;
			}
			
			if (y > 200 and y < 225) {
				menu_position = POSITION_AMATEUR;
			}
			
			if (y > 225 and y < 250) {
				menu_position = POSITION_PROFESSIONAL;
			}
		}
		
	} else {
		cout << MOVE_MOUSE_ERROR << endl;
		exit(EXIT_FAILURE);
	}
}
