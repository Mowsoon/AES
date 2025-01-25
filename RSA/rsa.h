#ifndef RSA_H
#define RSA_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RAND_SIZE 1024
#define E 65537
#define SHIFT 256

void generate_rsa_key(mpz_t e, mpz_t d, mpz_t n);
char * rsa(char *message, mpz_t key, mpz_t module);




#endif //RSA_H
