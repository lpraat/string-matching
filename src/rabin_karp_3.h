#pragma once

#include "core_types.h"
#include "utils.h"
#include "string_matcher.h"
#include <vector>
#include <string>

class RabinKarp3 : StringMatcher {

private:
    uint32 patHash = 0;
    uint32 textHash = 0;

    uint32 firstPower;

    uint32 p;

    uint32 M = 1024;

    uint32 base = 2;

public:
    explicit RabinKarp3(const std::string& pat) : StringMatcher(pat) {
    }

    void preprocess(const std::string& text, uint32 start) {
        patHash = 0;
        textHash = 0;


        firstPower = 1;
        for (uint32 _ = 0; _ < patLength - 1; _++) {
            firstPower = (base * firstPower) % p;
        }
        // or firstPower = modularExponentiation(2, patLength-1, p); using utils



        for (uint32 i = 0; i < patLength; i++) {
            patHash = (base * patHash + pat[i]) % p;
            textHash = (base * textHash + text[i+start]) % p;
        }

    }

    void updateTextHash(int32 i, const std::string& text) {
        // Using the modulus properties stabilize the result otherwise the following:
        // textHash = (textHash - (text[i] * firstPower)) * 2 + text[i + patLength];
        // textHash = textHash % p;
        // could go negative in the first parenthesis
        textHash = (textHash + p - firstPower*text[i] % p) % p;
        textHash = (textHash * base + text[i+patLength]) % p;
    }


    bool searchIn(const std::string& text, uint32* offset) override {
        p = generatePrime();
        preprocess(text, 0);

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
                } else {
                    p = generatePrime();
                    preprocess(text, i);
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