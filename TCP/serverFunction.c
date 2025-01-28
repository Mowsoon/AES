#include "serverFunction.h"

struct sockaddr_in configure_server_socket(void) {
    struct sockaddr_in serverSocket = {0};
    serverSocket.sin_family         = AF_INET;
    serverSocket.sin_port           = LISTEN_PORT;
    serverSocket.sin_addr.s_addr    = INADDR_ANY;

    return serverSocket;
}

void bind_socket(int socketFd, struct sockaddr_in serverSocket, int socketLength) {
    if (bind(socketFd, (struct sockaddr*)&serverSocket, socketLength) == -1) {
        handle_error("bind_fd");
    }
}

int accept_socket(int socketFd, struct sockaddr_in serverSocket, int socketLength) {
    int acceptFd = accept(socketFd, (struct sockaddr*)&serverSocket, &socketLength);
    if (acceptFd == -1) {
        handle_error("accept");
    }
    return acceptFd;
}