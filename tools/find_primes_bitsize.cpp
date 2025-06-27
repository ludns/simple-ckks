#include <iostream>
#include <vector>
#include <cmath>

bool is_prime(uint64_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

std::vector<uint64_t> find_primes_with_bit_size(int bit_size, int count, uint64_t modulus) {
    std::vector<uint64_t> primes;
    
    // Start from the smallest number with the given bit size
    uint64_t start = 1ULL << (bit_size - 1);
    uint64_t end = (1ULL << bit_size) - 1;
    
    // Find the first candidate that is ≡ 1 (mod modulus)
    uint64_t candidate = start - (start % modulus) + 1;
    
    while (primes.size() < count && candidate <= end) {
        if (is_prime(candidate)) {
            primes.push_back(candidate);
        }
        candidate += modulus;
    }
    
    return primes;
}

int main() {
    const uint64_t ring_size = 65536;
    const uint64_t modulus = 2 * ring_size; // 131072
    
    std::cout << "Finding primes for CKKS with ring size 2^16 = " << ring_size << std::endl;
    std::cout << "Primes must be ≡ 1 (mod " << modulus << ")" << std::endl << std::endl;
    
    // Find 24 primes of 41 bits (similar to the GPU library)
    std::cout << "Regular primes (41-bit):" << std::endl;
    auto primes_41 = find_primes_with_bit_size(41, 24, modulus);
    
    std::cout << "Found " << primes_41.size() << " primes of 41 bits:" << std::endl;
    for (auto p : primes_41) {
        std::cout << "  " << p << std::endl;
    }
    
    // Find 1 prime of 42 bits (for the initial modulus)
    std::cout << "\nInitial prime (42-bit):" << std::endl;
    auto primes_42 = find_primes_with_bit_size(42, 1, modulus);
    for (auto p : primes_42) {
        std::cout << "  " << p << std::endl;
    }
    
    // Find special primes of 42 bits
    std::cout << "\nSpecial primes (42-bit):" << std::endl;
    auto special_primes_42 = find_primes_with_bit_size(42, 3, modulus);
    
    std::cout << "Found " << special_primes_42.size() << " special primes of 42 bits:" << std::endl;
    for (auto p : special_primes_42) {
        std::cout << "  " << p << std::endl;
    }
    
    // Generate C++ code
    std::cout << "\nC++ code:" << std::endl;
    std::cout << "// Initial 42-bit prime" << std::endl;
    std::cout << "vector<uint64_t> primes = {" << primes_42[0];
    
    // Add 41-bit primes
    for (size_t i = 0; i < primes_41.size(); ++i) {
        std::cout << ", " << primes_41[i];
    }
    std::cout << "};" << std::endl;
    
    std::cout << "vector<uint64_t> special_primes = {";
    for (size_t i = 0; i < special_primes_42.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << special_primes_42[i];
    }
    std::cout << "};" << std::endl;
    
    // Calculate total bits
    int total_bits = 42 + 41 * primes_41.size();
    std::cout << "\nTotal coefficient modulus bits: " << total_bits << std::endl;
    std::cout << "Ring size: 2^16 = " << ring_size << std::endl;
    std::cout << "Scale: 2^41" << std::endl;
    
    return 0;
}