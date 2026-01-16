#include "../include/window.h"
#include <SDL2/SDL.h>
#include <stdio.h>


int initalization(App *app){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		printf("failed initalization %s", SDL_GetError());
		return 1;
	}

	app->window = SDL_CreateWindow("Chat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	
	if(app->window == NULL){
		printf("failed creating window %s", SDL_GetError());
		return 1;
	}

	app->renderer = SDL_CreateRenderer(app->window, -1, 0);

	if(app->renderer == NULL){
		printf("failed creating renderer %s", SDL_GetError());
		return 1;
	}
	return 0;
}

void cleanup(App *app){
	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
}

void clear_screen(App *app){
	SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	SDL_RenderClear(app->renderer);
}

void sdl_loop(App *app){
	int run = 1;
	while(run){
		while(SDL_PollEvent(&app->event)){
			switch(app->event.type){
			case SDL_QUIT:
				run = 0;
				break;
			}
		}
		frame_render(app);
	}
}

void frame_render(App *app){
	clear_screen(app);
	SDL_RenderPresent(app->renderer);
	SDL_Delay(1000/FPS);
}
