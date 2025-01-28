#ifndef SERVERFUNCTION_H
#define SERVERFUNCTION_H

#define LISTEN_PORT 8080
#define PENDING_QUEUE_SIZE 1
#define BUFFER_SIZE 1024

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include <stdio.h>
#include <stdint.h>


void init_winsock(void);
int init_socket(void);
struct sockaddr_in configure_server_socket(void);
void bind_socket(int socketFd, struct sockaddr_in serverSocket, int socketLength);
void handle_error(const char *functionName);
int accept_socket(int socketFd, struct sockaddr_in serverSocket, int socketLength);
void receiv_bytes(int connectedSocket, char buffer[1024]);
size_t send_data(int socket, const void* data, size_t size);
size_t receive_data(int socket, void *buffer, size_t size);
void print_bytes(const char *label, uint8_t *bytes, size_t size);

#endif
