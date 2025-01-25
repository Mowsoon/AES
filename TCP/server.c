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
        handle_error("listen");
    }

    puts("Waiting for a client connection...");

    int connectedSocket         = accept_socket(socket_fd, serverSocket, socketLength);
    char buffer[BUFFER_SIZE]    = {0};
    int receivedBytes           = receiv_bytes(connectedSocket, buffer);

    printf("Client has send : %s\n", buffer);

    const char message[] = "Hello Client!";
    int sentBytes = sent_bytes(connectedSocket, message);


    #ifdef _WIN32
        closesocket(connectedSocket);
        closesocket(socket_fd);
        WSACleanup();
    #else
        close(connectedSocket);
        close(socket_fd);
    #endif
    return 0;
}
