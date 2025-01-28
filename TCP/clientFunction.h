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
#include <stdint.h>

void init_winsock(void);
int init_socket(void);
struct sockaddr_in configure_client_socket(void);
void connect_client_socket(int socketFd, struct sockaddr_in clientSocket, int socketLength);
void send_message(int serverSocket, char buffer[BUFFER_SIZE]);
size_t receive_data(int socket, void *buffer, size_t size);
size_t send_data(int socket, const void *data, size_t size);
void receive_rsa_key_size(int socket, size_t *e_size, size_t *n_size);
void print_bytes(const char *label, uint8_t *bytes, size_t size);

#endif
