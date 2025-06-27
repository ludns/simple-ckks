#include <cstdio>
#include <vector>
#include <chrono>
#include <cstring>
#include "simple_ckks/simple_ckks.h"

using namespace std;
using namespace simple_ckks;
using namespace std::chrono;

int main() {
    printf("CKKS Demo\n");
    printf("================================\n");

    try {
        // Define parameters for CKKS
        vector<uint64_t> primes = {1152921504606748673, 576460752308273153, 576460752302473217};
        vector<uint64_t> special_primes = {0x7fffffffe0001, 0x80000001c0001, 0x80000002c0001, 0x7ffffffd20001};

        uint64_t poly_degree = 8192;
        double scale = 1ULL << 40;

        printf("Parameters:\n");
        printf("  Polynomial degree: %llu\n", (unsigned long long)poly_degree);
        printf("  Scale: 2^40\n");
        printf("  Number of primes: %zu\n", primes.size());

        // Initialize parameters
        Parameters params(scale, poly_degree, primes, special_primes);

        // Key generation
        printf("\nGenerating keys...\n");
        auto keygen_start = high_resolution_clock::now();

        Keygen keygen(params);
        SecretKey secret_key = keygen.generateSecretKey();
        PublicKey public_key = keygen.generatePublicKey();
        EvaluationKey eval_key = keygen.generateEvaluationKey();

        auto keygen_end = high_resolution_clock::now();
        auto keygen_duration = duration_cast<milliseconds>(keygen_end - keygen_start);
        printf("Key generation time: %lld ms\n", (long long)keygen_duration.count());

        // Create encoder and encryptor
        Encoder encoder(params);
        Encryptor encryptor(params);
        Evaluator evaluator(params, eval_key);

        // Test data
        vector<complex<double>> input_data = {3.14159, 2.71828, 1.41421, 1.61803};
        printf("\nInput data: ");
        for (const auto& val : input_data) {
            printf("%.5f ", val.real());
        }
        printf("\n");

        // Encoding
        printf("\nEncoding data...\n");
        auto encode_start = high_resolution_clock::now();

        Plaintext plaintext = encoder.encode(input_data);

        auto encode_end = high_resolution_clock::now();
        auto encode_duration = duration_cast<microseconds>(encode_end - encode_start);
        printf("Encoding time: %lld us\n", (long long)encode_duration.count());

        // Encryption
        printf("\nEncrypting data...\n");
        auto encrypt_start = high_resolution_clock::now();

        Ciphertext ciphertext = encryptor.encrypt(plaintext, public_key);

        auto encrypt_end = high_resolution_clock::now();
        auto encrypt_duration = duration_cast<milliseconds>(encrypt_end - encrypt_start);
        printf("Encryption time: %lld ms\n", (long long)encrypt_duration.count());

        // Perform a simple operation (add 1)
        printf("\nPerforming homomorphic addition of 1...\n");
        auto eval_start = high_resolution_clock::now();

        vector<complex<double>> addend = {1.0, 1.0, 1.0, 1.0};
        Plaintext add_plain = encoder.encode(addend);
        Ciphertext result = ciphertext;
        evaluator.addPlainInPlace(result, add_plain);

        auto eval_end = high_resolution_clock::now();
        auto eval_duration = duration_cast<milliseconds>(eval_end - eval_start);
        printf("Evaluation time: %lld ms\n", (long long)eval_duration.count());

        // Decryption
        printf("\nDecrypting result...\n");
        auto decrypt_start = high_resolution_clock::now();

        Plaintext decrypted_result = encryptor.decrypt(result, secret_key);

        auto decrypt_end = high_resolution_clock::now();
        auto decrypt_duration = duration_cast<milliseconds>(decrypt_end - decrypt_start);
        printf("Decryption time: %lld ms\n", (long long)decrypt_duration.count());

        // Decode
        printf("\nDecoding result...\n");
        auto decode_start = high_resolution_clock::now();

        vector<complex<double>> decoded_result = encoder.decode(decrypted_result);

        auto decode_end = high_resolution_clock::now();
        auto decode_duration = duration_cast<microseconds>(decode_end - decode_start);
        printf("Decoding time: %lld us\n", (long long)decode_duration.count());

        // Display results
        printf("\nResults (should be input + 1):\n");
        printf("Expected: ");
        for (size_t i = 0; i < input_data.size(); i++) {
            printf("%.5f ", input_data[i].real() + 1.0);
        }
        printf("\n");

        printf("Actual:   ");
        for (size_t i = 0; i < min(decoded_result.size(), input_data.size()); i++) {
            printf("%.5f ", decoded_result[i].real());
        }
        printf("\n");

        // Total time summary
        printf("\n=== Timing Summary ===\n");
        printf("Key generation: %lld ms\n", (long long)keygen_duration.count());
        printf("Encoding:       %lld us\n", (long long)encode_duration.count());
        printf("Encryption:     %lld ms\n", (long long)encrypt_duration.count());
        printf("Evaluation:     %lld ms\n", (long long)eval_duration.count());
        printf("Decryption:     %lld ms\n", (long long)decrypt_duration.count());
        printf("Decoding:       %lld us\n", (long long)decode_duration.count());

        auto total_time = keygen_duration.count() +
                         (encode_duration.count() / 1000.0) +
                         encrypt_duration.count() +
                         eval_duration.count() +
                         decrypt_duration.count() +
                         (decode_duration.count() / 1000.0);
        printf("Total time:     %.2f ms\n", total_time);

    } catch (const exception& e) {
        fprintf(stderr, "Exception caught: %s\n", e.what());
        return 1;
    } catch (...) {
        fprintf(stderr, "Unknown exception caught\n");
        return 1;
    }

    return 0;
}
