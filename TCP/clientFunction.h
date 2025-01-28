#ifndef CLIENTFUNCTION_H
#define CLIENTFUNCTION_H

#define CONNECTION_HOST "127.0.0.1"

#include "generalFunction.h"

void init_winsock(void);
int init_socket(void);
struct sockaddr_in configure_client_socket(void);
void connect_client_socket(int socketFd, struct sockaddr_in clientSocket, int socketLength);
size_t receive_data(int socket, void *buffer, size_t size);
size_t send_data(int socket, const void *data, size_t size);
void print_bytes(const char *label, uint8_t *bytes, size_t size);
void handle_error(const char *functionName);

#endif
