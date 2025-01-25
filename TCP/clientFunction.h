#ifndef CLIENTFUNCTION_H
#define CLIENTFUNCTION_H

#define LISTEN_PORT 8080
#define CONNECTION_HOST "127.0.0.1"
#define BUFFER_SIZE 1024

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
#endif

#include <stdio.h>

void init_winsock(void);
int init_socket(void);
struct sockaddr_in configure_client_socket(void);
void connect_client_socket(int socketFd, struct sockaddr_in clientSocket, int socketLength);
void send_bytes(int serverSocket, char buffer[BUFFER_SIZE]);
void receive_bytes(int connectedSocket, char buffer[BUFFER_SIZE]);

#endif
