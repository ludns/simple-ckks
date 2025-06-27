#include "simple_ckks/parameters.h"
#include "simple_ckks/public_key.h"
#include "simple_ckks/plaintext.h"
#include "simple_ckks/ciphertext.h"
#include "simple_ckks/secret_key.h"

#ifndef simple_ckks_ENCRYPTOR_H
#define simple_ckks_ENCRYPTOR_H

namespace simple_ckks {
    class Encryptor {
        Parameters params;
    public:
        explicit Encryptor(Parameters params);

        Ciphertext encrypt(Plaintext &plain, PublicKey &pub);

        Plaintext decrypt(Ciphertext &cipher, SecretKey &secret);

    };
}

#endif //simple_ckks_ENCRYPTOR_H
