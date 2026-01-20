#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define FPS           60 
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH  800

typedef struct {
	SDL_Window   *window;
	SDL_Event     event;
	SDL_Renderer *renderer;
}App;

int initalization(App *app);
void cleanup(App *app);
void clear_screen(App *app);
void sdl_loop(App *app);
void frame_render(App *app);

void input_box(App *app);

#endif

