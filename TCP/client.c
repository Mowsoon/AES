#include "clientFunction.h"
#include "../RSA/rsa.h"

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socketFd                        = init_socket();
    struct sockaddr_in clientSocket     = configure_client_socket();
    const int socketLength              = sizeof(clientSocket);
    connect_client_socket(socketFd, clientSocket, socketLength);

    mpz_t e, n;
    mpz_init(e); mpz_init(n);

    receive_value(socketFd, e);
    receive_value(socketFd, n);


    mpz_t value;
    mpz_init(value);
    mpz_set_ui(value, 42);
    rsa(value, value,e,n);

    send_value(socketFd, value);



    mpz_clear(value);
    mpz_clear(e);
    mpz_clear(n);

    #ifdef _WIN32
        closesocket(socketFd);
        WSACleanup();
    #else
        close(socket_fd);
    #endif
    return 0;
}
