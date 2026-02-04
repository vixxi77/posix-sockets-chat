#include "window.h"

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

static void message_log(int log);

void *client_socket(void *arg){
	App *app = arg;	

	message_log(1);
	while(app->running){
	}
	message_log(0);

	return NULL;
}

void message_log(int log){
	switch(log){
	case 1:
		printf("CLIENT NETWORK THREAD HAS STARTED ! \n");
		break;
	case 0:
		printf("CLIENT NETWORK THREAD EXITING... \n");
		break;
	case 2:
		printf("\rNETWORK IS LISTENING...");
		fflush(stdout);
	}
}
