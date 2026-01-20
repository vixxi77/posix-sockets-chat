#include "../include/server_network.h"

int main(void){
	server_socket("its a server");
	while(1){
	}
	server_socket("shutting down");
	return 0;
}
