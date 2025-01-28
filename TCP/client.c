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

    receive_message(socketFd, e);
    receive_message(socketFd, n);

    gmp_printf("e (as mpz_t): %Zd\n", e);


    mpz_t message, crypted;
    mpz_init(message);
    mpz_set_ui(message, 42);
    rsa(crypted, message,e,n);
    mpz_clear(message);





    mpz_clear(crypted);
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
