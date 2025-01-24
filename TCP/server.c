#include <stdio.h>

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif


void init_winsock(void) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", WSAGetLastError());
        exit(1);
    }
}

int init_socket(void) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        #ifdef _WIN32
            fprintf(stderr, "socket() failed with error: %d\n", WSAGetLastError());
        #else
            perror("socket");
        #endif
        exit(1);
    }
    return socket_fd;
}

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socket_fd = init_socket();

    #ifdef _WIN32
        WSACleanup();
        closesocket(socket_fd);
    #else
        close(socket_fd);
    #endif
    return 0;
}
