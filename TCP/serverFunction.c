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

size_t receive_data(int socket, void *buffer, size_t size) {
    size_t received = 0;
    while (received < size) {
        ssize_t bytes = recv(socket, (uint8_t *)buffer + received, size - received, 0);
        if (bytes == -1) {
            perror("recv");
            exit(EXIT_FAILURE);
        } else if (bytes == 0) {
            fprintf(stderr, "Connection closed by the server.\n");
            exit(EXIT_FAILURE);
        }
        received += bytes;
    }
    return received;
}


size_t send_data(int socket, const void* data, size_t size) {
    size_t sent = 0;
    while (sent < size) {
        ssize_t bytes = send(socket, (const uint8_t *) data + sent, size - sent, 0);
        if (bytes == -1) {
            handle_error("send");
        }
        sent += bytes;
    }
    return sent;
}