#ifndef RSA_H
#define RSA_H

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RAND_SIZE 512
#define E 65537
#define SHIFT 256

void generate_rsa_key(mpz_t e, mpz_t d, mpz_t n);
void rsa(mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulus);




#endif
