#include "clientFunction.h"

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socketFd                       = init_socket();
    struct sockaddr_in clientSocket    = configure_client_socket();
    const int socketLength              = sizeof(clientSocket);
    connect_client_socket(socketFd, clientSocket, socketLength);

    #ifdef _WIN32
        closesocket(socketFd);
        WSACleanup();
    #else
        close(socket_fd);
    #endif
    return 0;
}
