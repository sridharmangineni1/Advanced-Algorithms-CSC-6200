#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <bitset>
#include <cstdint>

// Constants used by SHA-256 algorithm (the first 32 bits of the fractional parts of the cube roots of the first 64 primes).
const uint32_t K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Bitwise operations for SHA-256
uint32_t rightRotate(uint32_t value, unsigned int count) {
    return (value >> count) | (value << (32 - count));
}

void sha256Transform(uint32_t state[8], const uint8_t block[64]) {
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t w[64];

    // Initialize variables
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    // Prepare message schedule
    for (int i = 0; i < 16; ++i) {
        w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | (block[i * 4 + 3]);
    }
    for (int i = 16; i < 64; ++i) {
        uint32_t s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
        uint32_t s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    // Compression function main loop
    for (int i = 0; i < 64; ++i) {
        uint32_t S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t temp1 = h + S1 + ch + K[i] + w[i];
        uint32_t S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    // Add this chunk's hash to result so far
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

void sha256(const std::string& input, std::vector<uint8_t>& digest) {
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // Pad the input
    uint64_t bitLen = input.size() * 8;
    std::vector<uint8_t> paddedInput(input.begin(), input.end());

    // Append a single '1' bit
    paddedInput.push_back(0x80);

    // Append 0 <= k < 512 bits '0', making the total length congruent to 448 mod 512
    while ((paddedInput.size() % 64) != 56) {
        paddedInput.push_back(0x00);
    }

    // Append the original message length as a 64-bit big-endian integer
    for (int i = 7; i >= 0; --i) {
        paddedInput.push_back((bitLen >> (i * 8)) & 0xff);
    }

    // Process the padded input in 512-bit (64-byte) chunks
    for (size_t i = 0; i < paddedInput.size(); i += 64) {
        sha256Transform(state, &paddedInput[i]);
    }

    // Produce the final hash
    digest.clear();
    for (int i = 0; i < 8; ++i) {
        digest.push_back((state[i] >> 24) & 0xff);
        digest.push_back((state[i] >> 16) & 0xff);
        digest.push_back((state[i] >> 8) & 0xff);
        digest.push_back(state[i] & 0xff);
    }
}

// Helper function to read file content
std::string readFile(const std::string& filename) {
    // Define the absolute path to the file
    std::string absolutePath = "C:\\Users\\sridh\\source\\repos\\ConsoleApplication10\\x64\\Debug\\" + filename;
    std::cout << "Trying to open file at: " << absolutePath << std::endl;  // Debugging: show the path being used
    std::ifstream file(absolutePath, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file at: " << absolutePath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Helper function to convert digest into hex string
std::string toHexString(const std::vector<uint8_t>& digest) {
    std::ostringstream result;
    for (const auto& byte : digest) {
        result << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return result.str();
}

int main() {
    std::string filename = "mark.txt"; 
    std::string fileContent = readFile(filename);

    if (fileContent.empty()) {
        std::cerr << "Failed to read the file or the file is empty!" << std::endl;
        return 1;
    }

    std::vector<uint8_t> hashDigest;
    sha256(fileContent, hashDigest);

    // Output the final SHA-256 hash in hexadecimal format
    std::string hashHex = toHexString(hashDigest);
    std::cout << "SHA-256 Hash: " << hashHex << std::endl;

    return 0;
}
