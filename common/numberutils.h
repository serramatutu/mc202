#include <stdlib.h>

/**
 * MDC (Greatest Common Divisor) 
*/
size_t gcd(size_t a, size_t b);

/**
 * Encontra números coprimos.
 * De acordo com a Wikipedia, há 60% de chance de números serem coprimos. Por isso,
 * a estratégia dessa função é simplesmente chutar valores até que eles sejam coprimos.
*/
size_t coprime(size_t seed, size_t val);