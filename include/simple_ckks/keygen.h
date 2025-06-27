#include "simple_ckks/util.h"
#include "simple_ckks/public_key.h"
#include "simple_ckks/secret_key.h"
#include "simple_ckks/parameters.h"
#include "simple_ckks/rand_util.h"
#include "simple_ckks/evaluation_key.h"

#ifndef simple_ckks_KEYGEN_H
#define simple_ckks_KEYGEN_H

namespace simple_ckks {
    class Keygen {
        Parameters params;
        SecretKey secretKey;
        bool secretKeyAttached = false;

    public:
        Keygen(Parameters params);

        Keygen(Parameters params, SecretKey secretKey);

        bool isSecretKeyAttached();

        SecretKey generateSecretKey();

        PublicKey generatePublicKey();

        EvaluationKey generateEvaluationKey();
    };
}

#endif //simple_ckks_KEYGEN_H
