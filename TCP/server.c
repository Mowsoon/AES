#include <stdio.h>

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif


int main() {
    printf("Hello server\n");
    return 0;
}