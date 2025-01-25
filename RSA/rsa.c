#include "rsa.h"

void init_random();
void generate_random_prime();
void find_pq();
void calculate_n_phi();
void calculate_d();
void string_to_mpz();
void mpz_to_string();

void generate_rsa_key(mpz_t e, mpz_t d, mpz_t n) {
    mpz_t p, q, phi;
    gmp_randstate_t state;

    init_random(state);
    find_pq(p, q, state);
    calculate_n_phi(p, q, n, phi);
    calculate_d(e, d, phi);

    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi);
    gmp_randclear(state);
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

void calculate_n_phi(mpz_t p, mpz_t q, mpz_t n, mpz_t phi) {
    mpz_init(n); mpz_init(phi);
    mpz_sub_ui(n, p, 1);
    mpz_sub_ui(phi, q, 1);
    mpz_mul(phi, n, phi);
    mpz_mul(n, p, q);
}

void calculate_d(mpz_t e, mpz_t d, mpz_t phi)
{
    mpz_init(e); mpz_init(d);
    mpz_set_ui(e, E);
    if (!(mpz_divisible_p(phi, e))) {
        mpz_invert(d, e, phi);
    }
    else {
        exit(EXIT_FAILURE);
    }
}


void rsa(mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_init(result);
    mpz_powm(result, base, exponent, modulus);
}