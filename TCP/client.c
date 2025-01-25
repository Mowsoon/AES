#include "clientFunction.h"

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif


    #ifdef _WIN32
        WSACleanup();
    #endif
    return 0;
}