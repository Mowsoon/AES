#include "clientFunction.h"
#include "serverFunction.h"



int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socket_fd                       = init_socket();
    struct sockaddr_in client_socket    = configure_client_socket();


    #ifdef _WIN32
        WSACleanup();
    #endif
    return 0;
}
