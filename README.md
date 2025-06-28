# Simple CKKS

A lightweight C++ implementation of the CKKS (Cheon-Kim-Kim-Song) homomorphic encryption scheme, optimized for embedded systems and cross-platform deployment.

## Overview

This library provides a clean, efficient implementation of CKKS homomorphic encryption, allowing you to perform computations on encrypted data. This implements the full RNS version of CKKS.

## Project Structure

```
simple-ckks/
├── include/simple_ckks/    # Header files
│   ├── simple_ckks.h      # Main include file
│   ├── parameters.h       # CKKS parameters
│   ├── encoder.h          # Encoding/decoding operations
│   ├── encryptor.h        # Encryption/decryption
│   ├── evaluator.h        # Homomorphic operations
│   ├── keygen.h           # Key generation
│   └── math/              # Mathematical operations
├── src/                   # Source files
├── test/                  # Unit tests
├── demo/                  # Demo application
│   └── ckks_demo.cpp     # Example usage with timing
├── CMakeLists.txt        # Build configuration
├── toolchain-aarch64.cmake # ARM cross-compilation settings
└── build scripts         # Convenience scripts
```

## Building

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler
- (Optional) aarch64 cross-compiler for ARM builds

### Native Build (macOS/Linux)

```bash
./build.sh
```

This will create a `build/` directory with:
- `libsimple_ckks.a` - Static library
- `tests` - Unit test executable
- `ckks_demo` - Demo application

### ARM Cross-Compilation

```bash
./build-arm.sh
```

This creates a `build-arm/` directory with the NXP ARM64 Cortex A35 binary `ckks_demo`.

### Build Scripts

- `./build.sh` - Full native build
- `./build-arm.sh` - Full ARM cross-compilation
- `./quick-build-arm.sh` - Fast NXP rebuild (source changes only)
- `./clean.sh` - Remove all build artifacts

## Usage Example

```cpp
#include "simple_ckks/simple_ckks.h"

using namespace simple_ckks;

// Set up parameters
vector<uint64_t> primes = {1152921504606748673, 576460752308273153, 576460752302473217};
vector<uint64_t> special_primes = {0x7fffffffe0001, 0x80000001c0001, 0x80000002c0001, 0x7ffffffd20001};
Parameters params(1ULL << 40, 8192, primes, special_primes);

// Generate keys
Keygen keygen(params);
SecretKey secret_key = keygen.generateSecretKey();
PublicKey public_key = keygen.generatePublicKey();
EvaluationKey eval_key = keygen.generateEvaluationKey();

// Encode and encrypt
Encoder encoder(params);
Encryptor encryptor(params);
vector<complex<double>> data = {3.14159, 2.71828, 1.41421, 1.61803};
Plaintext plaintext = encoder.encode(data);
Ciphertext ciphertext = encryptor.encrypt(plaintext, public_key);

// Perform homomorphic operations
Evaluator evaluator(params, eval_key);
vector<complex<double>> addend = {1.0, 1.0, 1.0, 1.0};
Plaintext add_plain = encoder.encode(addend);
evaluator.addPlainInPlace(ciphertext, add_plain);

// Decrypt and decode
Plaintext result_plain = encryptor.decrypt(ciphertext, secret_key);
vector<complex<double>> result = encoder.decode(result_plain);
```

## Demo Application

The included demo (`demo/ckks_demo.cpp`) demonstrates:
- Key generation
- Encoding/encryption
- Homomorphic addition
- Decryption/decoding
- Performance timing for each operation

Run it with:
```bash
./build/ckks_demo        # Native
./build-arm/ckks_demo    # On ARM board
```

## Deployment to Embedded Systems

To deploy to an NXP or similar ARM64 board:

1. Build for ARM:
   ```bash
   ./build-arm.sh
   ```

2. Copy to your board:
   ```bash
   scp build-arm/ckks_demo user@board-ip:/path/to/destination/
   ```

3. Run on the board:
   ```bash
   ssh user@board-ip
   ./ckks_demo
   ```

The demo will output timing information for all operations, helping you optimize parameters for your specific hardware.

## Parameter Tuning

Key parameters that affect performance and security:

- **Polynomial degree** (`poly_degree`)

- **Scale**: Typically 2^40
  - Affects precision of computations

- **Number of primes**: Affects the multiplicative depth
  - More primes = more multiplications possible
  - Also affects performance

## Testing

Run the unit tests:
```bash
./build/tests
```

Available test suites:
- Encoder: Encoding/decoding operations
- NTTransformer: Number theoretic transforms
- Encryptor: Encryption/decryption
- Evaluator: Homomorphic operations

## Performance

Typical performance on embedded ARM Cortex-A35 with secure parameters:
- Key generation: ~60s
- Encryption: ~60s
- Homomorphic addition: ~10s
- Decryption: ~1s

Performance varies based on polynomial degree and number of primes.
