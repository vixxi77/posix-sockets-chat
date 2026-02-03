#include "window.h"
#include "client_network.h"

#include <stdlib.h>
#include <pthread.h>


int main(void){
	App app = {0};

	pthread_t net_thread;

        if(initalization(&app) != 0) return EXIT_FAILURE;

	pthread_create(&net_thread, NULL, client_socket, &app);

	app.running = 1;
	while(app.running){
		sdl_frame(&app);
	}

	app.running = 0;
	pthread_join(net_thread, NULL);
	cleanup(&app);
	return 0;
}
