#pragma once

#include "core_types.h"
#include "utils.h"
#include "string_matcher.h"
#include <vector>
#include <string>

class RabinKarp1 : StringMatcher {

private:
    uint32 k;

    std::vector<uint32> patHash;
    std::vector<uint32> textHash;

    std::vector<uint32> firstPower;

    std::vector<uint32> p;

    uint32 M = 1024;

    uint32 base = 2;

public:
    explicit RabinKarp1(const std::string& pat, uint32 k = 10) : k(k), StringMatcher(pat), patHash(k), textHash(k), p(k), firstPower(k) {
    }

    void preprocess(const std::string& text) {
        for (uint32 i = 0; i < k; i++) {
            patHash[i] = 0;
            textHash[i] = 0;
        }

        for (uint32 i = 0; i < k; i++) {
            firstPower[i] = 1;
            for (uint32 _ = 0; _ < patLength - 1; _++) {
                firstPower[i] = (base * firstPower[i]) % p[i];
            }
        }

        // Could be easily computed in parallel
        //#pragma omp parallel for schedule(static)
        for (uint32 i = 0; i < k ; i++) {
            for (uint32 j = 0; j < patLength; j++) {
                patHash[i] = (base * patHash[i] + pat[j]) % p[i];
                textHash[i] = (base * textHash[i] + text[j]) % p[i];
            }
        }
    }

    void updateTextHash(uint32 i, const std::string& text) {

        // Could be easily computed in parallel
        //#pragma omp parallel for schedule(static)
        for (uint32 j = 0; j < k; j++) {
            textHash[j] = (textHash[j] + p[j] - (text[i] * firstPower[j]) % p[j]) % p[j];
            textHash[j] = (textHash[j] * base + text[i + patLength]) % p[j];
        }
    }


    bool searchIn(const std::string& text, uint32* offset) override {
        for (uint32 i = 0; i < k; i++) {
            p[i] = generatePrime();
        }

        preprocess(text);
        uint32 textLength = text.length();

        for (uint32 i = 0; i <= textLength - patLength; i++) {
            bool match = true;

            for (uint32 j = 0; j < k; j++) {
                if (patHash[j] != textHash[j]) {
                    match = false;
                }
            }

            if (match) {
                *offset = i;
                return true;
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