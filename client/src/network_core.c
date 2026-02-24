#include "network_core.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define PORT 9009
#define SERVER_IP "127.0.0.1"

char message_data[64];


int socket_init(struct sockaddr_in *address){
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1){
		return -1;
	}


	address->sin_family = AF_INET;
	address->sin_port   = htons(PORT);
	address->sin_addr.s_addr = inet_addr(SERVER_IP);

	int connection_status = connect(socketfd, (struct sockaddr*)address, sizeof(*address));
	if(connection_status == -1){
		printf("cant establish a connection.. Will retry.. \n");
		close(socketfd);
		return -1;
	}
	
	return socketfd;
}

void socket_loop(int socketfd){
		int bytes = recv(socketfd, message_data, sizeof(message_data) - 1, 0);

		if(bytes > 0){
			message_data[bytes] = '\0';
			printf("Message received: %s\n", message_data);
		}else if(bytes == 0){
			printf("closing connection \n");
			socket_cleanup(&socketfd);
		}
}

void socket_cleanup(int *socketfd){
	if(*socketfd >= 0){
		close(*socketfd);
		*socketfd = -1;
	}
}

int socket_retry(int retry_seconds){
	struct timespec ts;
	static double last_time = 0;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	double current_time = ts.tv_sec;

	if(current_time - last_time >= retry_seconds){
		printf("RETRYING CONNECTION \n");
		last_time = current_time;
		return 1;
	}
	return 0;
}

