#include "simple_ckks/math/polynomial.h"
#include "simple_ckks/math/ntt_transformer.h"
#include "simple_ckks/parameters.h"
#include <random>

#ifndef simple_ckks_RAND_UTIL_H
#define simple_ckks_RAND_UTIL_H

namespace simple_ckks {
    uint64_t getRandom(uint64_t end);

    void sampleHWT(vector<Polynomial<uint64_t>> &poly, vector<Polynomial<uint64_t>> &polyP, vector<uint64_t> &primes,
                   vector<uint64_t> &specialPrimes);

    long long getRandomError();

    void samplePolynomial(vector<Polynomial<uint64_t>> &poly, vector<uint64_t> &primes, bool isForPublic);

    void sampleDoublePolynomial(vector<Polynomial<uint64_t>> &polyQ, vector<Polynomial<uint64_t>> &polyP,
                                vector<uint64_t> &primesQ, vector<uint64_t> &primesP);

    void sampleErrorAndAdd(vector<Polynomial<uint64_t>> &poly, vector<uint64_t> &primes, NTTTransformer &transformer);

    void sampleDoubleErrorAndAdd(vector<Polynomial<uint64_t>> &polyQ, vector<Polynomial<uint64_t>> &polyP,
                                 vector<uint64_t> &primesQ, vector<uint64_t> &primesP, NTTTransformer &transformerQ,
                                 NTTTransformer &transformerP);

    void sampleSingleErrorAndAdd(Polynomial<uint64_t>& poly, int level, Parameters& givenParams);

    void sampleDoublePolynomialWithSeed(vector<Polynomial<uint64_t>> &polyQ, vector<Polynomial<uint64_t>> &polyP,
                                vector<uint64_t> &primesQ, vector<uint64_t> &primesP, uint64_t seed);
}

#endif //simple_ckks_RAND_UTIL_H
