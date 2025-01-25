#include "serverFunction.h"

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socketFd                       = init_socket();
    struct sockaddr_in serverSocket     = configure_server_socket();
    const int socketLength              = sizeof(serverSocket);
    bind_socket(socketFd, serverSocket, socketLength);

    if (listen(socketFd,PENDING_QUEUE_SIZE) == -1) {
        handle_error("listen");
    }

    puts("Waiting for a client connection...");

    int connectedSocket         = accept_socket(socketFd, serverSocket, socketLength);
    char buffer[BUFFER_SIZE]    = {0};

    receiv_bytes(connectedSocket, buffer);
    printf("Client has send : %s\n", buffer);

    const char message[] = "Hello Client!";
    sent_bytes(connectedSocket, message);


    #ifdef _WIN32
        closesocket(connectedSocket);
        closesocket(socketFd);
        WSACleanup();
    #else
        close(connectedSocket);
        close(socket_fd);
    #endif
    return 0;
}
