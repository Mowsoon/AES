#include "clientFunction.h"
#include "serverFunction.h"
#include "../RSA/rsa.h"


void print_bytes(const char *label, uint8_t *bytes, size_t size) {
    printf("%s (size: %zu): ", label, size);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}


int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socketFd                        = init_socket();
    struct sockaddr_in clientSocket     = configure_client_socket();
    const int socketLength              = sizeof(clientSocket);
    connect_client_socket(socketFd, clientSocket, socketLength);

    // Réception des tailles de e et n
    uint32_t e_size_net, n_size_net;
    receive_data(socketFd, &e_size_net, sizeof(e_size_net));
    receive_data(socketFd, &n_size_net, sizeof(n_size_net));

    // Convertir les tailles du format réseau vers le format hôte
    size_t e_size = ntohl(e_size_net);
    size_t n_size = ntohl(n_size_net);



    uint8_t *e_data = malloc(e_size);
    uint8_t *n_data = malloc(n_size);
    if (!e_data || !n_data) {
        handle_error("Error allocating memory\n");
    }

    // Réception des données de e et n
    receive_data(socketFd, e_data, e_size);
    receive_data(socketFd, n_data, n_size);

    print_bytes("e : ", e_data, e_size);
    print_bytes("n : ", n_data, n_size);

    free(e_data);
    free(n_data);



    #ifdef _WIN32
        closesocket(socketFd);
        WSACleanup();
    #else
        close(socket_fd);
    #endif
    return 0;
}
