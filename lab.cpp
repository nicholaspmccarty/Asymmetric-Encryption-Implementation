#include <cstdint>
#include <iostream> 

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
    // TODO 1
    return 0;
}
// Checks to see if n is a prime number
bool isPrime(uint64_t n) {
    // TODO 2
    return false;
}
// Generates a random prime number between 1 and n
uint64_t generateRandomPrime(uint64_t n) {
    // TODO 3
    return 0;
}
// Given p, and q, find a number that is relatively prime to (p-1)*(q-1)
// I.e. the gcd(k_e, (p-1)*(q-1))==1
uint64_t calculatePublicKey(uint64_t p, uint64_t q) {
    // TODO 4
    return 0;
}
// Given p, q, and k_e, calculate the private key which satisfies
// (k_e*k_d) % ((p-1)(q-1)) == 1
uint64_t calculatePrivateKey(uint64_t p, uint64_t q, uint64_t k_e) {
    // TODO 5
    return 0;
}

// Generates a random public/private key-pair
// such that n > message_max.
KeyPair generateKeyPair(int32_t message_max) {
    // TODO 6
    return KeyPair();
}
// Encrypts an integer message using a product and an encryption key.
// Error if m > n
uint64_t encrypt(uint64_t m, uint64_t n, uint64_t k_e) {
    //TODO 7
    return 0;
}
// Decrypts anuint64_t message given a ciphertext c, N, private decryption key
// Error if m > n
uint64_t decrypt(uint64_t c, uint64_t n, uint64_t k_d) {
    // TODO 8
    return 0;
}

int main() {
    // TODO 9
    uint64_t k_e = 17;
    uint64_t k_d = 71153;
    uint64_t n = 152021;

    return 0;
}