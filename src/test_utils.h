#pragma once

#include "core_types.h"
#include <string>
#include <vector>

const char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_-";


std::string generateTestStringAscii(uint32 strLength, uint32 alphabetSize = 64) {
    std::vector<char> text(strLength);

    for (uint32 i = 0; i < strLength; i++) {
        text[i] = alphabet[rand() % alphabetSize];
    }

    return std::string(text.data(), text.size());
}

std::string generatePatternAscii(uint32 patLength, uint32 alphabetSize = 64) {
    std::vector<char> pattern(patLength);

    for (uint32 i = 0; i < patLength; i++) {
        pattern[i] = alphabet[rand() % alphabetSize];
    }

    return std::string(pattern.data(), pattern.size());

}