#include "simple_ckks/public_key.h"

namespace simple_ckks {
    PublicKey::PublicKey(vector<Polynomial<uint64_t>> polyA, vector<Polynomial<uint64_t>> polyB)
            : polyA(polyA), polyB(polyB) {}

    Polynomial<uint64_t> PublicKey::getA(int level) {
        return polyA[level];
    }

    Polynomial<uint64_t> PublicKey::getB(int level) {
        return polyB[level];
    }


    PublicKey::PublicKey() {}

    int PublicKey::getLevels() {
        return polyA.size();
    }
}
