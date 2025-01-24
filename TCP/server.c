#include <stdio.h>

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
    void init_winsock(void) {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            fprintf(stderr, "WSAStartup failed with error: %d\n", WSAGetLastError());
            exit(1);
        }
    }
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif


#define LISTEN_PORT 8080;

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

struct sockaddr_in configure_server_socket() {
        struct sockaddr_in serverSocket;
        serverSocket.sin_family = AF_INET;
        serverSocket.sin_port = LISTEN_PORT;
        serverSocket.sin_addr.s_addr = INADDR_ANY;

        return serverSocket;
    }

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

    int socket_fd = init_socket();
    struct sockaddr_in serverSocket = configure_server_socket();

    #ifdef _WIN32
        WSACleanup();
        closesocket(socket_fd);
    #else
        close(socket_fd);
    #endif
    return 0;
}
