#include "simple_ckks/parameters.h"
#include "simple_ckks/plaintext.h"
#include "simple_ckks/math/rns_converter.h"
#include <vector>
#include <complex>

#ifndef simple_ckks_ENCODER_H
#define simple_ckks_ENCODER_H

using namespace std;

namespace simple_ckks {
    class Encoder {
        Parameters parameters;
        vector<complex<double>> rootAtPower;
        vector<int> indexHash;
        RNSConverter converter;

    public:
        Encoder(Parameters &givenParameters);

        Plaintext encode(vector<complex<double>> toEncode);

        Plaintext encode(vector<double> toEncode);

        void setParameters(Parameters &givenParameters);

        Parameters getParameters();

        vector<complex<double>> decode(Plaintext &givenPlaintext);
    };
}

#endif //simple_ckks_ENCODER_H
