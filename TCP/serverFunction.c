#include "serverFunction.h"

void init_winsock(void) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}

int init_socket(void) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        #ifdef _WIN32
            fprintf(stderr, "socket() failed with error: %d\n", WSAGetLastError());
        #else
            perror("socket");
        #endif
        exit(EXIT_FAILURE);
    }
    return socket_fd;
}

struct sockaddr_in configure_server_socket(void) {
    struct sockaddr_in serverSocket;
    serverSocket.sin_family         = AF_INET;
    serverSocket.sin_port           = LISTEN_PORT;
    serverSocket.sin_addr.s_addr    = INADDR_ANY;

    return serverSocket;
}

int bind_socket(int socket_fd, struct sockaddr_in serverSocket, int socketLength) {
    int bind_fd = bind(socket_fd, (struct sockaddr*)&serverSocket, socketLength);
    if (bind_fd == -1) {
        #ifdef _WIN32
            fprintf(stderr, "bind() failed with error: %d\n", WSAGetLastError());
        #else
            perror("bind");
        #endif
        exit(EXIT_FAILURE);
    }
    return bind_fd;
}
