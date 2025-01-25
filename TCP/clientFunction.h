#ifndef CLIENTFUNCTION_H
#define CLIENTFUNCTION_H

#ifdef _WIN32 // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else //Linux
    #include <netinet/in.h>
    #include <sys/socket.h>
#endif

#include <stdio.h>

void init_winsock(void);


#endif
