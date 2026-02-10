#ifndef _NCORE_T
#define _NCORE_T

#include <netinet/in.h>

int socket_init(struct sockaddr_in *address);
void socket_loop(int socketfd);
void socket_cleanup(int *sokcetfd);
int socket_retry(int retry_seconds);

#endif
