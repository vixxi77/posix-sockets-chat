#include "window.h"
#include "client_network.h"
#include <stdlib.h>


int main(void){
	App app = {0};
	client_socket("its a client");
        if(initalization(&app) != 0) return EXIT_FAILURE;

	app.running = 1;
	while(app.running){
		sdl_frame(&app);
	}

	client_socket("shutting down");
	cleanup(&app);
	return 0;
}
