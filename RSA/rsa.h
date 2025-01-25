#ifndef RSA_H
#define RSA_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RAND_SIZE 1024
#define E 65537

void generate_rsa_key(mpz_t e, mpz_t d, mpz_t n);
char * crypt_rsa(char *message, mpz_t e, mpz_t n);
char * decrypt_rsa(char *message, mpz_t d, mpz_t n);



#endif //RSA_H
