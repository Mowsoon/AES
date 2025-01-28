#include "serverFunction.h"

int main() {
    mpz_t e, d, n;
    generate_rsa_key(e, d, n);


    #ifdef _WIN32
        init_winsock();
    #endif

    int socketFd                        = init_socket();
    struct sockaddr_in serverSocket     = configure_server_socket();
    const int socketLength              = sizeof(serverSocket);
    bind_socket(socketFd, serverSocket, socketLength);

    if (listen(socketFd,PENDING_QUEUE_SIZE) == -1) {
        handle_error("listen");
    }

    puts("Waiting for a client connection...");

    int connectedSocket = accept_socket(socketFd, serverSocket, socketLength);


    send_value(connectedSocket, e);
    send_value(connectedSocket, n);

    mpz_t value;
    mpz_init(value);

    receive_value(connectedSocket, value);
    rsa(value, value, d, n);

    gmp_printf("%Zd\n", value);


    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(n);


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
