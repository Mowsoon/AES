#include "rsa.h"

void init_random();

void generate_rsa_key(mpz_t e, mpz_t d, mpz_t n) {
    mpz_t p, q, phi;
    gmp_randstate_t state;

    init_random();
}

void init_random(gmp_randstate_t state) {
    gmp_randinit_default(state);
    unsigned long seed = time(NULL);
    gmp_randseed_ui(state, seed);
}

