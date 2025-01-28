#include "clientFunction.h"
#include "generalFunction.h"

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

void receive_rsa_key_size(int socket, size_t *e_size, size_t *n_size) {
    uint32_t e_size_net, n_size_net;
    receive_data(socket, &e_size_net, sizeof(e_size_net));
    receive_data(socket, &n_size_net, sizeof(n_size_net));

    *e_size = ntohl(e_size_net);
    *n_size = ntohl(n_size_net);
}