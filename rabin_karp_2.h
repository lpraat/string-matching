#pragma once

#include <vector>
#include <string>
#include <cmath>
#include "core_types.h"
#include "utils.h"
#include "string_matcher.h"
#include <iostream>

class RabinKarp2 : StringMatcher {

private:
    uint32 patLength;

    uint32 patHash = 0;
    uint32 textHash = 0;

    uint32 firstPower;

    uint32 p;

    uint32 M = 1024;


public:
    explicit RabinKarp2(const std::string& pat) : StringMatcher(pat) {
        patLength = pat.length();
    }

    void preprocess(const std::string& text) {
        patHash = 0;
        textHash = 0;

        firstPower = 1;
        for (uint32 _ = 0; _ < patLength - 1; _++) {
            firstPower = (2 * firstPower) % p;
        }


        for (uint32 i = 0; i < patLength; i++) {
            patHash = (2 * patHash + pat[i]) % p;
            textHash = (2 * textHash + text[i]) % p;
        }
    }

    void updateTextHash(uint32 i, const std::string& text) {
        // Using the modulus properties stabilize the result otherwise the following:
        // textHash = (textHash - (text[i] * firstPower)) * 2 + text[i + patLength];
        // textHash = textHash % p;
        // could go negative in the first parenthesis
        textHash = (textHash + p - firstPower*text[i] % p) % p;
        textHash = (textHash * 2 + text[i+patLength]) % p;
    }


    bool searchIn(const std::string& text, uint32* offset) override {
        p = generatePrime();
        preprocess(text);

        uint32 textLength = text.length();

        for (uint32 i = 0; i <= textLength - patLength; i++) {
            if (patHash == textHash) {

                bool match = true;
                for (uint32 k = 0; k < patLength; k++) {
                    if (text[i + k] != pat[k]) {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    *offset = i;
                    return true;
                }
            }

            if (i < textLength - patLength) {
                updateTextHash(i, text);
            }
        }

        return false;
    }


    uint32 generatePrime() {
        uint32 random = 1 + rand() % M;

        while (!isPrime(random)) {
            random = 1 + rand() % M;
        }

        return random;
    }
};