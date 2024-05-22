#include <cstdint>
#include <cstring>

namespace lasd {

/* ************************************************************************** */

template <>
class Hashable<int> {
public:
    // Knuth's multiplicative hash function
    unsigned long operator()(const int& data) const noexcept {
        // Define the Knuth constant, which is 2^32 * (sqrt(5) - 1) / 2
        const unsigned long knuth_constant = 2654435761u;
        
        // Calculate the hash value by multiplying the key with the Knuth constant
        // The resulting value is the hash value for the given key
        return data * knuth_constant;
    }
};

template <>
class Hashable<double> {
public:
    // XOR-folding hash function for double
    unsigned long operator()(const double& data) const noexcept {
        // Convert the double to its binary representation
        uint64_t binaryRep;
        std::memcpy(&binaryRep, &data, sizeof(data));

        // XOR-folding: split the 64-bit binaryRep into two 32-bit parts and XOR them together
        uint32_t high = static_cast<uint32_t>(binaryRep >> 32);
        uint32_t low = static_cast<uint32_t>(binaryRep & 0xFFFFFFFF);

        // Combine the two 32-bit parts using XOR to get the final hash value
        return (high ^ low);
    }
};

template <>
class Hashable<std::string> {
public:
    // djb2 hash function for strings
    unsigned long operator()(const std::string& data) const noexcept {
        unsigned long hash = 5381; // Initialize hash value with a magic number

        // Iterate over each character in the string
        for (char c : data) {
            // Multiply the current hash value by 33 and add the current character
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }

        return hash;
    }
};

}
