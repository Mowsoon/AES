#include "serverFunction.h"
#include "generalFunction.h"

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

void send_rsa_key_size(int connectedSocket, size_t e_size, size_t n_size) {
    uint32_t e_size_net = htonl((uint32_t)e_size);
    uint32_t n_size_net = htonl((uint32_t)n_size);

    send_data(connectedSocket, &e_size_net, sizeof(e_size_net));
    send_data(connectedSocket, &n_size_net, sizeof(n_size_net));
}