#include "serverFunction.h"
#include "../RSA/rsa.h"

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
    size_t e_size, n_size;
    uint8_t e_bytes[BUFFER_SIZE], n_bytes[BUFFER_SIZE];

    mpz_export(e_bytes, &e_size, 1, sizeof(uint8_t), 0, 0, e);
    mpz_export(n_bytes, &n_size, 1, sizeof(uint8_t), 0, 0, n);


    print_bytes("E value :", e_bytes, e_size);
    print_bytes("N value :", n_bytes, n_size);

    send_rsa_key_size(connectedSocket, e_size, n_size);

    send_data(connectedSocket, e_bytes, e_size);
    send_data(connectedSocket, n_bytes, n_size);


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
