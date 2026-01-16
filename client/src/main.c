#include "../include/window.h"
#include <stdlib.h>

int main(void){
	App app = {0};
        if(initalization(&app) != 0) exit(EXIT_FAILURE);
	sdl_loop(&app);
	cleanup(&app);
	return 0;
}
