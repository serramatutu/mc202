#include "numberutils.h"

size_t gcd(size_t a, size_t b) {
    while (b != 0) {
        size_t temp = a;
        a = b;
        b = temp % b;
    }

    return a;
}

size_t coprime(size_t seed, size_t val) {
    srand(seed);

    size_t fac;
    do {
        fac = rand();
    } while (gcd(fac, val) != 1);

    return fac;
}