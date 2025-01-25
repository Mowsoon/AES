#include "rsa.h"

void init_random();
void generate_random_prime();
void find_pq();

void generate_rsa_key(mpz_t e, mpz_t d, mpz_t n) {
    mpz_t p, q, phi;
    gmp_randstate_t state;

    init_random(state);
    find_pq(p, q, state);
}

void init_random(gmp_randstate_t state) {
    gmp_randinit_default(state);
    unsigned long seed = time(NULL);
    gmp_randseed_ui(state, seed);
}

void generate_random_prime(mpz_t prime, gmp_randstate_t state) {
    mpz_urandomb(prime, state, RAND_SIZE);
    mpz_nextprime(prime, prime);
}

void find_pq(mpz_t p, mpz_t q, gmp_randstate_t state) {
    mpz_init(p); mpz_init(q);
    generate_random_prime(p, state);
    generate_random_prime(q, state);
}