cmake_minimum_required(VERSION 3.29)
project(projet_perso_AES)
set(CMAKE_C_STANDARD 11)

include_directories(C:/gmp)
link_directories(C:/gmp/.libs)


add_executable(server TCP/server.c
        TCP/serverFunction.c
        TCP/serverFunction.h
        RSA/rsa.h
        RSA/rsa.c)
add_executable(client TCP/client.c
        TCP/clientFunction.c
        TCP/clientFunction.h
        RSA/rsa.h
        RSA/rsa.c)

target_link_libraries(server gmp)
target_link_libraries(client gmp)

if (WIN32)
    target_link_libraries(server ws2_32)
    target_link_libraries(client ws2_32)
endif()