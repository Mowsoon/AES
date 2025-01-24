#include "serverFunction.h"

void handle_error(const char *function_name) {
    #ifdef _WIN32
        fprintf(stderr, "%s failed with error: %d\n", function_name, WSAGetLastError());
    #else
        perror(function_name);
    #endif
    exit(EXIT_FAILURE);
}

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
        handle_error("socket");
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
        handle_error("bind_fd");
    }
    return bind_fd;
}


