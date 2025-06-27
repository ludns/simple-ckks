#include "simple_ckks/math/polynomial.h"
#include "simple_ckks/parameters.h"
#include "simple_ckks/util.h"

#ifndef simple_ckks_PUBLIC_KEY_H
#define simple_ckks_PUBLIC_KEY_H

namespace simple_ckks {
    class PublicKey {
        vector<Polynomial<uint64_t>> polyA, polyB;

    public:
        PublicKey(vector<Polynomial<uint64_t>> polyA, vector<Polynomial<uint64_t>> polyB);

        PublicKey();

        int getLevels();

        Polynomial<uint64_t> getA(int level);

        Polynomial<uint64_t> getB(int level);

    };
}

#endif //simple_ckks_PUBLIC_KEY_H
