#include "serverFunction.h"

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socket_fd                       = init_socket();
    struct sockaddr_in serverSocket     = configure_server_socket();
    const int socketLength              = sizeof(serverSocket);
    int bind_fd                         = bind_socket(socket_fd, serverSocket, socketLength);

    if (listen(socket_fd,PENDING_QUEUE_SIZE) == -1) {
        #ifdef _WIN32
            fprintf(stderr, "Error while listening on socket: %d\n", WSAGetLastError());
        #else
            perror("Error while listening on socket");
        #endif
        exit(EXIT_FAILURE);
    }

    #ifdef _WIN32
        WSACleanup();
        closesocket(socket_fd);
    #else
        close(socket_fd);
    #endif
    return 0;
}
