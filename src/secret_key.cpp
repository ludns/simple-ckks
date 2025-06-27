#include "simple_ckks/secret_key.h"

namespace simple_ckks {
    SecretKey::SecretKey(int levels, int specialLevels, int ringDegree) : polyQ(levels,
                                                                                Polynomial<uint64_t>(ringDegree)),
                                                                          polyP(specialLevels,
                                                                                Polynomial<uint64_t>(ringDegree)) {}

    SecretKey::SecretKey(vector<Polynomial<uint64_t>> givenPolyQ, vector<Polynomial<uint64_t>> givenPolyP) : polyQ(
            givenPolyQ), polyP(givenPolyP) {}

    Polynomial<uint64_t> &SecretKey::getPolyQ(int level) {
        return polyQ[level];
    }

    vector<Polynomial<uint64_t>> &SecretKey::getPolysQ() {
        return polyQ;
    }

    vector<Polynomial<uint64_t>> &SecretKey::getPolysP() {
        return polyP;
    }

    Polynomial<uint64_t> &SecretKey::getPolyP(int level) {
        return polyP[level];
    }


    SecretKey::SecretKey() {}
}
