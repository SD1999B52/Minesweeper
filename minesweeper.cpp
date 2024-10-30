#include "Window.h"

#define INIT_SDL_ERROR "main: Sdl initialization error."

const float FPS  = 60.0;
const float WAIT = 1000.0 / FPS;

int main(int argc, char** args) {
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << INIT_SDL_ERROR << endl;
		exit(EXIT_FAILURE);
	}
	
	Window window;
	SDL_Event event;
	
	Uint64 last = 0;
	
	bool quit = false;
	
	while (quit == false) {
		while (SDL_PollEvent(&event)) {
			
			int x = event.motion.x;
			int y = event.motion.y;
			
			if (event.type == SDL_QUIT) {quit = true;}
			
			//событие перемещения мыши
			if (event.type == SDL_MOUSEMOTION) {
				window.move_mouse(x, y);
			}
			
			//событие нажатия кнопок мыши
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				
				if (event.button.button 
				== SDL_BUTTON_LEFT) {
					window.left_click(x, y);
				}
				
				if (event.button.button 
				== SDL_BUTTON_RIGHT) {
					window.right_click(x, y);
				}
			}
		}
		
		//ограничение кадров
		Uint64 current = SDL_GetTicks();
		Uint64 past    = current - last;
		
		if (past > WAIT) {
			window.redraw();
			last = current;
		}
	}
	
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
