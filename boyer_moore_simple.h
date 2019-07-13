#pragma once

#include <vector>
#include <string>
#include "core_types.h"
#include "string_matcher.h"

class BoyerMooreSimple : StringMatcher {

private:
    std::vector<uint32> delta1;
    std::vector<uint32> delta2;

public:
    explicit BoyerMooreSimple(const std::string& pat) : StringMatcher(pat) {
        initializeDelta1();
    }

    void initializeDelta1() {
        delta1 = std::vector<uint32>(128);

        for (uint32 i = 0; i < delta1.size(); i++) {
            delta1[i] = patLength;
        }

        // why i < patLength - 1? because if i = patlength - i
        // delta1[pat[i]] = patLength - (patLength - 1) - 1 = 0 which means no shift
        for (uint32 i = 0; i < patLength - 1; i++) {
            delta1[pat[i]] = patLength - i - 1;
        }

    }

    bool searchIn(const std::string& text, uint32* offset) override {
        uint32 patLength = pat.length();
        uint32 textLength = text.length();

        uint32 i, j;

        // Use auxiliary k otherwise in text "ab ab abc def" and pattern is "xy abc" -> infinite loop
        uint32 k = patLength - 1;

        while (k < textLength) {
            j = patLength - 1;
            i = k;

            while (text[i] == pat[j]) {
                i--;

                if (j == 0) {
                    *offset = i+1;
                    return true;
                }

                j--;


            }

            k += delta1[text[k]];
        }
        return false;
    }

    const std::vector<uint32>& getDelta1() const {
        return delta1;
    }

    const std::vector<uint32>& getDelta2() const {
        return delta2;
    }

    const std::string& getPat() const {
        return pat;
    }
};