#include "window.h"
#include "network_core.h"

#include <arpa/inet.h>
#include <sys/socket.h>

void *client_socket(void *arg){
	App *app = arg;	
	
	struct sockaddr_in address;

	int socketfd = socket_init(&address);
	

	while(app->running){
		if(socketfd < 0){
			if(socket_retry(5)){
				socketfd = socket_init(&address);
			}
		}

		socket_loop(socketfd);
	}

	socket_cleanup(&socketfd);

	return NULL;
}

