#include "simple_ckks/parameters.h"
#include "simple_ckks/evaluation_key.h"
#include "simple_ckks/ciphertext.h"
#include "simple_ckks/plaintext.h"
#include "simple_ckks/math/rns_transformer.h"

#ifndef simple_ckks_EVALUATOR_H
#define simple_ckks_EVALUATOR_H

namespace simple_ckks {
    class Evaluator {
        Parameters params;
        EvaluationKey evk;
        RNSTransformer rnsTransformer;

    public:
        Evaluator(Parameters params, EvaluationKey evk);

        void rescaleInPlace(Ciphertext &cipher);

        void multiplyRelinInPlace(Ciphertext &cipherA, Ciphertext &cipherB);

        void multiplyPlainInPlace(Ciphertext &cipher, Plaintext &plaintext);

        void addPlainInPlace(Ciphertext &cipher, Plaintext &plaintext);

        void addCipherInPlace(Ciphertext &cipherA, Ciphertext &cipherB);

        void negateInPlace(Ciphertext &cipher);
    };
}

#endif //simple_ckks_EVALUATOR_H
