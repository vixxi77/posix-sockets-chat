#include "window.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#define CENTERED 1
#define MAX_CHARACTERS 1024


SDL_Rect cursor_placeholder = {
	 10,
       	 765,
       	 10,
       	 20
};

SDL_Rect input = {0};


static TTF_Font *default_font;
static SDL_Color white = {255, 255, 255, 255};
static char TEXT_BUFFER[MAX_CHARACTERS] = {0};

void splash_screen(SDL_Renderer *renderer);
void render_helper_text(SDL_Renderer *renderer, 
		        TTF_Font *font,  
			const char *text, 
			int y, 
			SDL_Color color, 
		        int bound_width, 
			int bound_height, 
			int local_y, 
			int x);

void render_input_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect *rect, char *text, int y, int x, SDL_Color);
void cursor(SDL_Renderer *renderer, SDL_Rect *cursor, const SDL_Rect *input_offset);
void render_toolbar(SDL_Renderer *renderer, const char *text, TTF_Font *font, SDL_Color color);
void render_char_count(SDL_Renderer *renderer, const char *text);

int char_count(int len, int max);

int cursor_blink(void);

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

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
		printf("failed to load image format");
		return -1;
	}

	if(TTF_Init() == -1){
		printf("failed to initialize TTF \n");
		return -1;
	}
	
	default_font = TTF_OpenFont("./assets/FSEX300.ttf", 18);
	if(!default_font){
		printf("cant load font");
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
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void clear_screen(App *app){
	SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
	SDL_RenderClear(app->renderer);
}

void sdl_frame(App *app){
	SDL_Event event;
	
	SDL_StartTextInput();

	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			app->running = 0;
		}else if(event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN){
			if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(TEXT_BUFFER) > 0){
				TEXT_BUFFER[strlen(TEXT_BUFFER) - 1] = '\0';
			}else if(event.type == SDL_TEXTINPUT && char_count(strlen(TEXT_BUFFER), MAX_CHARACTERS) != -1){
				strncat(TEXT_BUFFER, event.text.text, sizeof(TEXT_BUFFER) - strlen(TEXT_BUFFER) - 1);
			}
		}
	}
	frame_render(app);
}

void frame_render(App *app){
	clear_screen(app);

	//TESTING PLACEHOLDER
	input_box(app->renderer);
	splash_screen(app->renderer);
	render_helper_text(app->renderer, default_font, "Welcome To SATURN", 460, white, WINDOW_WIDTH, WINDOW_HEIGHT, 0, CENTERED);
	render_helper_text(app->renderer, default_font, "Version: 0.0.1a", 480, white, WINDOW_WIDTH, WINDOW_HEIGHT, 0, CENTERED);
	render_helper_text(app->renderer, default_font, "Made By: vixxi77", 500, white, WINDOW_WIDTH, WINDOW_HEIGHT, 0, CENTERED);
	render_helper_text(app->renderer, default_font, "type  :create <Room Name>  to create a room", 540, white, WINDOW_WIDTH, WINDOW_HEIGHT, 0, CENTERED);
	render_helper_text(app->renderer, default_font, "type  :join   <Room Code>  to enter a room ", 560, white, WINDOW_WIDTH, WINDOW_HEIGHT, 0, CENTERED);
	render_helper_text(app->renderer, default_font, "type  :leave               to leave a room ", 580, white, WINDOW_WIDTH, WINDOW_HEIGHT, 0, CENTERED);
	render_input_text(app->renderer, default_font, &input, TEXT_BUFFER, 766, 10, white);
	render_toolbar(app->renderer, TEXT_BUFFER, default_font, white);
	render_char_count(app->renderer, TEXT_BUFFER);

	if(cursor_blink()){
		cursor(app->renderer, &cursor_placeholder, &input);
	}
	
	SDL_RenderPresent(app->renderer);
	SDL_Delay(1000/FPS);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////



//THIS IS ALSO TESTING PLACEHOLDER
void input_box(SDL_Renderer *renderer){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, 0, 750, 800, 750);
	SDL_RenderDrawLine(renderer, 0, 747, 800, 747);
}

void splash_screen(SDL_Renderer *renderer){
	SDL_Surface *splash;
	SDL_Rect rect = {100, 20, 600, 600};
	splash = IMG_Load("./assets/black_saturn_400.png");
	if(!splash){
		printf("cant load the image \n");
	}
	SDL_Texture *PNG = SDL_CreateTextureFromSurface(renderer, splash);
	SDL_RenderCopy(renderer, PNG, NULL, &rect);
	SDL_DestroyTexture(PNG);
	SDL_FreeSurface(splash);
}

void render_helper_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, int y, SDL_Color color, int bound_width, int bound_height, int local_y, int alignment){
	if(!font || !text) return;
	
	SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
	if(!surface){
		printf("TTF Render error %s", TTF_GetError());
		return;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture){
		printf("SDL Surface error %s", SDL_GetError());
		SDL_FreeSurface(surface);
		return;
	}

	int drawY = local_y + y;
	int x = 0;
	int textHeight, textWidth;
	TTF_SizeText(font, text, &textWidth, &textHeight);
	if(y < 0 || y + textHeight > bound_height) return;
	if(alignment == 1){
		x = (bound_width - textWidth) / 2;
	}else{
		x = alignment;
	}

	SDL_Rect rect = {x, drawY, textWidth, textHeight};

	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void render_input_text(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect *rect, char *text, int y, int x, SDL_Color color){

	if(!font || !text || text[0] == '\0'){
		rect->w = 0;
		return;
	} 

	SDL_Surface *surface;
	
	surface = TTF_RenderText_Solid(font, text, color);
	if(!surface){
		printf("TTF Render error %s \n", TTF_GetError());
		return;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture){
		printf("SDL Surface error %s", SDL_GetError());
		SDL_FreeSurface(surface);
		return;
	}

	int textHeight, textWidth;
	int charWidth;
	TTF_SizeText(font, text, &textWidth, &textHeight);
	TTF_SizeText(font, "A", &charWidth, NULL);

	int boxWidth = WINDOW_WIDTH - 20;
	int max_chars = boxWidth / charWidth;
	int baseX = x;
	int len = strlen(text);
	int overflow = 0;

	if(len > max_chars){
		overflow = len - max_chars;
	}

	rect->x = baseX - (overflow * charWidth);
	rect->y = y;
	rect->w = textWidth;
	rect->h = textHeight;

	SDL_RenderCopy(renderer, texture, NULL, rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void render_toolbar(SDL_Renderer *renderer, const char *text, TTF_Font *font, SDL_Color color){
	if(!text || text[0] == '\0') return;

	SDL_Rect rect = {0, 450, 500, 300};

	if(strcmp(text, ":help") == 0){
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);
		render_helper_text(renderer, font, "<LIST OF COMMANDS>", 20, color, rect.w, rect.h, rect.y, CENTERED);
		render_helper_text(renderer, font, ":setname <Your Name>    - sets your username", 60, color, rect.w, rect.h, rect.y, 20);
		render_helper_text(renderer, font, ":list                   - lists available rooms", 80, color, rect.w, rect.h, rect.y, 20);
		render_helper_text(renderer, font, ":help                   - lists available commands", 120, color, rect.w, rect.h, rect.y, 20);
		render_helper_text(renderer, font, ":create  <Room Name>    - creates a room", 160, white, rect.w, rect.h, rect.y, 20);
		render_helper_text(renderer, font, ":join    <Room Code>    - enters a room", 180, white, rect.w, rect.h, rect.y, 20);
		render_helper_text(renderer, font, ":leave                  - leave a room", 200, white, rect.w, rect.h, rect.y, 20);
		render_helper_text(renderer, font, "Press ENTER to execute commands", 240, white, rect.w, rect.h, rect.y, CENTERED);
	}

}

void render_char_count(SDL_Renderer *renderer, const char *text){

	int len = strlen(text);
	char count_string[12];

	snprintf(count_string, sizeof(count_string), "<%d/1024>", len);
	if(strlen(text) > 0){
		render_helper_text(renderer, default_font, count_string, 720, white, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 700);
	}
}

int char_count(int len, int max){
	int count = len;
	if(len == max){
		return -1;
	}
	return count;
}

void cursor(SDL_Renderer *renderer, SDL_Rect *cursor, const SDL_Rect *input_offset){
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	int baseX = 10;
	int maxX = WINDOW_WIDTH - 18;

	cursor->x = baseX + input_offset->w;

	if(cursor->x > maxX){
		cursor->x = maxX;
	}
	SDL_RenderFillRect(renderer, cursor);
}

int cursor_blink(){
	static int on = 1;
	static Uint32 last_toggle = 0;

	Uint32 now = SDL_GetTicks();

	if (now - last_toggle > 500){
		on = !on;
		last_toggle = now;
	}

	return on;
}

