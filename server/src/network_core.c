#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define PORT 9009

static char connect_message[64] = "Connected to server";

int socket_init(struct sockaddr_in *address){
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd == -1){
		return -1;
	}

        address->sin_family = AF_INET;
        address->sin_port   = htons(PORT);
        address->sin_addr.s_addr = INADDR_ANY;

	if(bind(socketfd, (struct sockaddr*)address, sizeof(*address)) == -1){
		printf("cant bind to socket \n");
		close(socketfd);
		return -1;
	}

	if(listen(socketfd, 1) == -1){
		close(socketfd);
		return -1;
	}
	

        return socketfd;
}

void socket_loop(int socketfd){
	struct sockaddr_in client_address;
	socklen_t address_len = sizeof(client_address);

	int client_socket = accept(socketfd, (struct sockaddr*)&client_address, &address_len);

	if(client_socket == -1){
		perror("no client");
		return;
	}

	printf("Connection from: %s \n", inet_ntoa(client_address.sin_addr));

	send(client_socket, connect_message, strlen(connect_message), 0);
	close(client_socket);
}

void socket_cleanup(int *socketfd){
	if(*socketfd >= 0){
		close(*socketfd);
		*socketfd = -1;
	}
}
