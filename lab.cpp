#include <cstdint>
#include <iostream> 
#include <expected>
#include <iostream>
#include <algorithm> 
#include <cstdlib>
#include <ctime>

// The output of a public-private key pair generator
struct KeyPair {
    // Random prime numbers
    uint64_t p;
    uint64_t q;

    // Product of random prime numbers
    uint64_t n;

    // Public encryption key
    uint64_t k_e;

    // Private decryption key
    uint64_t k_d;
};

enum class [[nodiscard]] Status {
    ok,
    invalid_input,
    unexpected_condition,
    data_loss_error
};



template <typename T>
using StatusOr = std::expected<T, Status>;

// Compute base^exponent mod modulus without needing to calculate base^exponent (very large)
uint64_t mod_exp(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent /= 2;
        base = (base * base) % modulus;
    }
    return result;
}

// Greatest common divisor
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
// Checks to see if n is a prime number
bool isPrime(uint64_t n) {
    if (n <= 1) {
        return false;
    }

    for (uint64_t i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}
// Generates a random prime number between 1 and n
uint64_t generateRandomPrime(uint64_t n) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    uint64_t randomPrime;
    do {
        // Generate a random number between 1 and n
        randomPrime = static_cast<uint64_t>(std::rand() % static_cast<int>(n) + 1);
    } while (!isPrime(randomPrime));

    return randomPrime;
    return 0;
}

// Given p, and q, find a number that is relatively prime to (p-1)*(q-1)
// I.e. the gcd(k_e, (p-1)*(q-1))==1
uint64_t calculatePublicKey(uint64_t p, uint64_t q) {
    // TODO 4
    uint64_t k_e = 0;
    while (gcd(k_e, (p-1)*(q-1)) != 1) {
        k_e += 2;
    }

    return k_e;
}
// Given p, q, and k_e, calculate the private key which satisfies
// (k_e*k_d) % ((p-1)(q-1)) == 1
uint64_t calculatePrivateKey(uint64_t p, uint64_t q, uint64_t k_e) {
    uint64_t phiN = (p - 1) * (q - 1);

    for (uint64_t kd = 1; kd < phiN; ++kd) {
        if ((k_e * kd) % phiN == 1) {
            return kd;
        }
    }

    return 0;
}

// Generates a random public/private key-pair
// such that n > message_max.
KeyPair generateKeyPair(int32_t message_max) {
    // TODO 6
    KeyPair ret;
    uint64_t p = generateRandomPrime(static_cast<uint64_t>(message_max));
    uint64_t q = generateRandomPrime(static_cast<uint64_t>(message_max));
    ret.p = p;
    ret.q = q;
    (void) ret;
    ret .n = ret.p * ret.q;
    // Setting k_e and k_d variables
    ret.k_e = calculatePublicKey(ret.p, ret.q);
    ret.k_d = calculatePrivateKey(ret.p, ret.q, ret.k_e);
    return ret;
}
// Encrypts an integer message using a product and an encryption key.
// Error if m > n
StatusOr<uint64_t> encrypt(uint64_t m, uint64_t n, uint64_t k_e) {
    if (m > n) {
        return std::unexpected(Status::data_loss_error);
    }
    
    return mod_exp(m, k_e, n);

}
// Decrypts anuint64_t message given a ciphertext c, N, private decryption key
// Error if m > n
StatusOr<uint64_t> decrypt(uint64_t c, uint64_t n, uint64_t k_d) {
    if (c > n) {
        return std::unexpected(Status::data_loss_error);
    }

   uint64_t decrypted_message = mod_exp(c, k_d, n);
   return decrypted_message;
}

int main() {
     std::string message = "Hello World!";
    uint64_t k_e = 17;
    uint64_t k_d = 71153;
    uint64_t n = 152021;
    (void) k_e;
    (void) k_d;
    (void) n;

    return 0;
}