#include "simple_ckks/util.h"
#include "simple_ckks/math/polynomial.h"

#ifndef simple_ckks_EVALUATION_KEY_H
#define simple_ckks_EVALUATION_KEY_H

namespace simple_ckks {
    class EvaluationKey {
    public:
        vector<Polynomial<uint64_t>> aP, aQ, bP, bQ;

        EvaluationKey(vector<Polynomial<uint64_t>> &aP, vector<Polynomial<uint64_t>> &aQ,
                      vector<Polynomial<uint64_t>> &bP,
                      vector<Polynomial<uint64_t>> &bQ);

        EvaluationKey();

    };
}

#endif //simple_ckks_EVALUATION_KEY_H
