#include "clientFunction.h"

void handle_error(const char *functionName) {
    #ifdef _WIN32
        fprintf(stderr, "Client: %s failed with error: %d\n", functionName, WSAGetLastError());
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

struct sockaddr_in configure_client_socket(void) {
    struct sockaddr_in client_socket;
    client_socket.sin_family        = AF_INET;
    client_socket.sin_port          = LISTEN_PORT;
    int inetReturnCode              = inet_pton(AF_INET, CONNECTION_HOST, &client_socket.sin_addr);
    if (inetReturnCode == -1) {
        handle_error("inet_pton");
    }
    return client_socket;
}

void connect_client_socket(int socketFd, struct sockaddr_in clientSocket, int socketLength) {
    if(connect(socketFd, (struct sockaddr *)&clientSocket, sizeof(clientSocket)) == -1) {
        handle_error("connect");
    }
}

void send_message(int serverSocket, char buffer[BUFFER_SIZE]) {
    if (send(serverSocket, buffer, BUFFER_SIZE, 0) == -1) {
        handle_error("send");
    }
}

void receive_bytes(int serverSocket, char buffer[BUFFER_SIZE]) {
    if (recv(serverSocket, buffer, BUFFER_SIZE, 0) == -1) {
        handle_error("recv");
    }
}