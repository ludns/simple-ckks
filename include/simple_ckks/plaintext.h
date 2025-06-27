#include "simple_ckks/math/polynomial.h"
#include "simple_ckks/parameters.h"
#include "simple_ckks/util.h"

using namespace std;

#ifndef simple_ckks_PLAINTEXT_H
#define simple_ckks_PLAINTEXT_H

namespace simple_ckks {
    class Plaintext {
        vector<Polynomial<uint64_t>> polynomials;
        Parameters parameters;
        int currentLevel;

    public:
        Plaintext(vector<vector<uint64_t>> &givenCoefficients, Parameters &parameters);

        Plaintext(vector<Polynomial<uint64_t>> polynomials, Parameters params, int level);

        Polynomial<uint64_t> &getPolynomial(int modIndex);

        void add(Plaintext &otherPlain, int modulusLevel);

        int getLevel();

        void decreaseLevel(int howMany);
    };
}

#endif //simple_ckks_PLAINTEXT_H
