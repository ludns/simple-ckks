#include "simple_ckks/parameters.h"
#include "simple_ckks/util.h"
#include "../lib/BigInt.h"

#ifndef simple_ckks_RNS_CONVERTER_H
#define simple_ckks_RNS_CONVERTER_H

namespace simple_ckks {
    class RNSConverter {
        vector<BigInt> qPerLevel;
        vector<vector<BigInt>> crtTransformation;
        Parameters params;
    public:
        explicit RNSConverter(Parameters &params);

        void scaleDownFromCRT(vector<vector<uint64_t>> &coeffsInCRT, vector<complex<double>> &destination);
    };
}

#endif //simple_ckks_RNS_CONVERTER_H
