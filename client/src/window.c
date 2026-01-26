#include "window.h"
#include <SDL2/SDL.h>
#include <stdio.h>

/*
TESTING PLACEHOLDER
SDL_Rect cursor_placeholder = {
	 10,
       	 760,
       	 10,
       	 30
};
*/
	



int initalization(App *app){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("failed initalization %s", SDL_GetError());
		return -1;
	}

	app->window = SDL_CreateWindow("Chat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	
	if(app->window == NULL){
		printf("failed creating window %s", SDL_GetError());
		cleanup(app);
		return -1;
	}

	app->renderer = SDL_CreateRenderer(app->window, -1, 0);

	if(app->renderer == NULL){
		printf("failed creating renderer %s", SDL_GetError());
		cleanup(app);
		return -1;
	}
	return 0;
}

void cleanup(App *app){
	if(app->renderer){
		SDL_DestroyRenderer(app->renderer);
		app->renderer = NULL;
	}

	if(app->window){
		SDL_DestroyWindow(app->window);
		app->window = NULL;
	}
	SDL_Quit();
}

void clear_screen(App *app){
	SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	SDL_RenderClear(app->renderer);
}

void sdl_frame(App *app){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			app->running = 0;
		}
	}
	frame_render(app);
}

//THIS IS ALSO TESTING PLACEHOLDER
void input_box(App *app){
	SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(app->renderer, 0, 750, 800, 750);
}

/*
TESTING PLACEHOLDER
void cursor(App *app, SDL_Rect *cursor){
	SDL_SetRenderDrawColor(app->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(app->renderer, cursor);
}

int cursor_blink(void){
	static int on = 1;
	static Uint32 last_toggle = 0;

	Uint32 now = SDL_GetTicks();

	if (now - last_toggle > 500){
		on = !on;
		last_toggle = now;
	}

	return on;
}
*/

void frame_render(App *app){
	clear_screen(app);

	//TESTING PLACEHOLDER
	input_box(app);
	
	/*
	TESTING PLACEHOLDER
	if(cursor_blink()){
		cursor(app, &cursor_placeholder);
	}
	*/

	SDL_RenderPresent(app->renderer);
	SDL_Delay(1000/FPS);
}
