
#include "generalFunction.h"




void handle_error(const char *functionName) {
    #ifdef _WIN32
        fprintf(stderr, "%s failed with error: %d\n", functionName, WSAGetLastError());
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

void print_bytes(const char *label, uint8_t *bytes, size_t size) {
    printf("%s (size: %zu): ", label, size);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}


void send_value(int socket, mpz_t data) {
    size_t data_size;
    uint8_t bytes[BUFFER_SIZE];

    mpz_export(bytes, &data_size, 1, sizeof(uint8_t), 0, 0, data);

    uint32_t data_size_net = htonl((uint32_t)data_size);
    send_data(socket, &data_size_net, sizeof(data_size_net));

    send_data(socket, bytes, data_size);
}

void receive_value(int socket, mpz_t value) {
    uint32_t data_size_net;
    receive_data(socket, &data_size_net, sizeof(data_size_net));
    size_t data_size = ntohl(data_size_net);

    uint8_t *data = malloc(data_size);
    if (data == NULL) {
        handle_error("malloc");
    }

    receive_data(socket, data, data_size);
    mpz_import(value, data_size, 1, sizeof(uint8_t), 0, 0, data);
    free(data);
}