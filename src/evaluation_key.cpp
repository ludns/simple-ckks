#include "simple_ckks/evaluation_key.h"

namespace simple_ckks {
    EvaluationKey::EvaluationKey(vector<Polynomial<uint64_t>> &aP, vector<Polynomial<uint64_t>> &aQ,
                                 vector<Polynomial<uint64_t>> &bP, vector<Polynomial<uint64_t>> &bQ) : aP(aP), aQ(aQ),
                                                                                                       bP(bP), bQ(bQ) {}

    EvaluationKey::EvaluationKey() {}

}
