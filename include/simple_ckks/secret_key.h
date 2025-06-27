#include "simple_ckks/math/polynomial.h"
#include "simple_ckks/parameters.h"
#include "simple_ckks/util.h"

#ifndef simple_ckks_SECRET_KEY_H
#define simple_ckks_SECRET_KEY_H

namespace simple_ckks {
    class SecretKey {
        vector<Polynomial<uint64_t>> polyQ;
        vector<Polynomial<uint64_t>> polyP;

    public:
        SecretKey(int levels, int specialLevels, int ringDegree);

        SecretKey();

        SecretKey(vector<Polynomial<uint64_t>> givenPolyQ, vector<Polynomial<uint64_t>> givenPolyP);

        Polynomial<uint64_t> &getPolyQ(int level);

        Polynomial<uint64_t> &getPolyP(int level);

        vector<Polynomial<uint64_t>> &getPolysQ();

        vector<Polynomial<uint64_t>> &getPolysP();

    };
}

#endif //simple_ckks_SECRET_KEY_H
