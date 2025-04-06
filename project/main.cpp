#include <iostream>
#include <string>
#include "md5.h"

int main() {
    while (true) {
        std::cout << "Input: ";
        std::string s;
        if (!std::getline(std::cin, s) || s.empty()) {
            break;
        }

        std::vector<uint8_t> hash = MD5((const uint8_t*)s.data(), s.size());
        std::string hexStr = md5hash_to_string(hash.data());

        std::cout << "MD5 hash: " << hexStr << std::endl << std::endl;
    }

    return 0;
}
