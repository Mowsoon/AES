#ifndef SERVERFUNCTION_H
#define SERVERFUNCTION_H
#define LISTEN_PORT 8080

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include <stdio.h>

void init_winsock(void);
int init_socket(void);
struct sockaddr_in configure_server_socket(void);
int bind_socket(int socket_fd, struct sockaddr_in serverSocket, int socketLength);

#endif
