#include "network_core.h"

#include <stdio.h>

int main(void){
	struct sockaddr_in address;
	int socketfd = socket_init(&address);
	if(socketfd < 0) return -1;

	printf("SERVER IS RUNNING HIDE!!! \n");

	while(1){
		socket_loop(socketfd);
	}

	socket_cleanup(&socketfd);
	return 0;
}
