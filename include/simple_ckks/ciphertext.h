#include "simple_ckks/math/polynomial.h"
#include "simple_ckks/parameters.h"

#ifndef simple_ckks_CIPHERTEXT_H
#define simple_ckks_CIPHERTEXT_H

namespace simple_ckks {
    class Ciphertext {
        vector<Polynomial<uint64_t>> polysA, polysB;
        int level;

    public:
        Ciphertext(int level, vector<Polynomial<uint64_t>> polysA, vector<Polynomial<uint64_t>> polysB);

        Ciphertext();

        Polynomial<uint64_t> &getPolyA(int givenLevel);

        Polynomial<uint64_t> &getPolyB(int givenLevel);

        vector<Polynomial<uint64_t>> &getPolysB();

        vector<Polynomial<uint64_t>> &getPolysA();

        int getLevel();

        void decreaseLevel(int howMany);

    };
}

#endif //simple_ckks_CIPHERTEXT_H
