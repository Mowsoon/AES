
#ifndef GENERALFUNCTION_H
#define GENERALFUNCTION_H

#define BUFFER_SIZE 1024
#define LISTEN_PORT 8080

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



void init_winsock(void);
int init_socket(void);
void handle_error(const char *functionName);
size_t receive_data(int socket, void *buffer, size_t size);
size_t send_data(int socket, const void *data, size_t size);
void print_bytes(const char *label, uint8_t *bytes, size_t size);

#endif