#ifndef SERVERFUNCTION_H
#define SERVERFUNCTION_H


#define PENDING_QUEUE_SIZE 1

#include "generalFunction.h"

void init_winsock(void);
int init_socket(void);
struct sockaddr_in configure_server_socket(void);
void bind_socket(int socketFd, struct sockaddr_in serverSocket, int socketLength);
int accept_socket(int socketFd, struct sockaddr_in serverSocket, int socketLength);
size_t send_data(int socket, const void* data, size_t size);
size_t receive_data(int socket, void *buffer, size_t size);
void send_rsa_key_size(int connectedSocket, size_t e_size, size_t n_size);
void handle_error(const char *functionName);
void print_bytes(const char *label, uint8_t *bytes, size_t size);

#endif
