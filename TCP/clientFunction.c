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

void get_rsa_key_size(int socket, size_t *e_size, size_t *n_size) {
    int socketFd;
    // Réception des tailles de e et n
    uint32_t e_size_net, n_size_net;
    receive_data(socket, &e_size_net, sizeof(e_size_net));
    receive_data(socket, &n_size_net, sizeof(n_size_net));

    *e_size = ntohl(e_size_net);
    *n_size = ntohl(n_size_net);
}

void print_bytes(const char *label, uint8_t *bytes, size_t size) {
    printf("%s (size: %zu): ", label, size);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}