#include "clientFunction.h"

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socket_fd                       = init_socket();
    struct sockaddr_in client_socket    = configure_client_socket();
    const int socketLength              = sizeof(client_socket);
    connect_client_socket(socket_fd, client_socket, socketLength);

    #ifdef _WIN32
        closesocket(socket_fd);
        WSACleanup();
    #else
        close(socket_fd);
    #endif
    return 0;
}
