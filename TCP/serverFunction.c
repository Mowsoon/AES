#include "serverFunction.h"

void handle_error(const char *functionName) {
    #ifdef _WIN32
        fprintf(stderr, "Server: %s failed with error: %d\n", functionName, WSAGetLastError());
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
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1) {
        handle_error("socket");
    }
    return socketFd;
}

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

int receiv_bytes(int connectedSocket, char buffer[1024]) {
    int receivedBytes = recv(connectedSocket, buffer, BUFFER_SIZE, 0);
    if (receivedBytes == -1) {
        handle_error("recv");
    }
    return receivedBytes;
}


int sent_bytes(int connectedSocket, char buffer[1024]) {
    int sentBytes = send(connectedSocket, buffer, BUFFER_SIZE, 0);
    if (sentBytes == -1) {
        handle_error("send");
    }
    return sentBytes;
}