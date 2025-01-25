cmake_minimum_required(VERSION 3.29)
project(projet_perso_AES)
set(CMAKE_C_STANDARD 11)


add_executable(server TCP/server.c
        TCP/serverFunction.c
        TCP/serverFunction.h)
add_executable(client TCP/client.c
        TCP/clientFunction.c
        TCP/clientFunction.h)

add_executable(rsa RSA/rsaMain.c)

if (WIN32)
    target_link_libraries(server ws2_32)
    target_link_libraries(client ws2_32)
endif()