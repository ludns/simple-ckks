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

int main() {
    const uint64_t ring_size = 65536;
    const uint64_t modulus = 2 * ring_size; // 131072
    
    std::cout << "Finding primes for CKKS with ring size 2^16 = " << ring_size << std::endl;
    std::cout << "Primes must be ≡ 1 (mod " << modulus << ")" << std::endl << std::endl;
    
    // Find primes around 60 bits
    std::vector<uint64_t> primes;
    std::vector<uint64_t> special_primes;
    
    // Start from 60-bit range
    uint64_t start = 1ULL << 59;
    uint64_t candidate = start - (start % modulus) + 1;
    
    int total_bits = 0;
    
    std::cout << "Regular primes (60-bit range):" << std::endl;
    while (primes.size() < 14 && candidate < (1ULL << 61)) {
        if (is_prime(candidate)) {
            primes.push_back(candidate);
            int bits = 64 - __builtin_clzll(candidate);
            total_bits += bits;
            std::cout << "  " << candidate << " (" << bits << " bits)" << std::endl;
        }
        candidate += modulus;
    }
    
    std::cout << "\nTotal bits so far: " << total_bits << std::endl;
    
    // Find special primes (smaller, around 50 bits)
    std::cout << "\nSpecial primes (50-bit range):" << std::endl;
    start = 1ULL << 49;
    candidate = start - (start % modulus) + 1;
    
    while (special_primes.size() < 4 && candidate < (1ULL << 51)) {
        if (is_prime(candidate)) {
            special_primes.push_back(candidate);
            int bits = 64 - __builtin_clzll(candidate);
            std::cout << "  0x" << std::hex << candidate << std::dec 
                      << " (" << bits << " bits)" << std::endl;
        }
        candidate += modulus;
    }
    
    std::cout << "\nC++ code:" << std::endl;
    std::cout << "vector<uint64_t> primes = {";
    for (size_t i = 0; i < primes.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << primes[i];
    }
    std::cout << "};" << std::endl;
    
    std::cout << "vector<uint64_t> special_primes = {";
    for (size_t i = 0; i < special_primes.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << "0x" << std::hex << special_primes[i] << std::dec;
    }
    std::cout << "};" << std::endl;
    
    std::cout << "\nTotal prime bits: ~" << total_bits << std::endl;
    std::cout << "Ring size: 2^16 = " << ring_size << std::endl;
    
    return 0;
}