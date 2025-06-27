#include <cstdint>
#include <complex>
#include <vector>

using namespace std;

#ifndef simple_ckks_UTIL_H
#define simple_ckks_UTIL_H

namespace simple_ckks {
    uint64_t modMultiply(uint64_t a, uint64_t b, uint64_t mod);

    uint64_t modAdd(uint64_t a, uint64_t b, uint64_t mod);

    uint64_t fastExp(uint64_t base, uint64_t exponent, uint64_t mod);

    void bitReverse(vector<uint64_t> &vec);
}

#endif //simple_ckks_UTIL_H
