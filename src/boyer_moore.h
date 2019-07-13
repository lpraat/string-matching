#pragma once

#include <vector>
#include <string>
#include "core_types.h"
#include "string_matcher.h"

class BoyerMoore : StringMatcher {

private:
    std::vector<uint32> delta1;
    std::vector<uint32> delta2;

public:
    explicit BoyerMoore(const std::string& pat) : StringMatcher(pat) {
        initializeDelta1();
        initializeDelta2();
    }

    void initializeDelta1() {
        delta1 = std::vector<uint32>(128);

        for (uint32 i = 0; i < delta1.size(); i++) {
            delta1[i] = patLength;
        }

        // why i < patLength - 1? because if i = patlength - 1
        // delta1[pat[i]] = patLength - (patLength - 1) - 1 = 0 which means no shift
        for (uint32 i = 0; i < patLength - 1; i++) {
            delta1[pat[i]] = patLength - i - 1;
        }

    }


    void initializeDelta2() {
        std::vector<uint32> delta2Tmp(patLength+1);
        std::vector<uint32> f(patLength+1);

        for (uint32 k = 1; k <= patLength; k++) {
            delta2Tmp[k] = 2 * (patLength) - k;
        }

        uint32 j = patLength;
        uint32 t = patLength+1;

        while (j > 0) {
            f[j] = t;

            while (t <= patLength && (pat[j-1] != pat[t-1])) {
                delta2Tmp[t] = std::min(delta2Tmp[t], patLength - j);
                t = f[t];
            }

            t--;
            j--;
        }

        for (int32 k = 1; k <= t; k++) {
            delta2Tmp[k] = std::min(delta2Tmp[k], patLength + t - k);
        }

        delta2 = std::vector<uint32>(patLength);
        for (uint32 i = 1; i < delta2Tmp.size(); i++) {
            delta2[i - 1] = delta2Tmp[i];
        }
    }



    bool searchIn(const std::string& text, uint32* offset) override {
        uint32 patLength = pat.length();
        uint32 textLength = text.length();

        uint32 i = patLength - 1;
        uint32 j;

        while (i < textLength) {

            j = patLength - 1;

            while (text[i] == pat[j]) {
                i--;

                if (j == 0) {
                    *offset = i+1;
                    return true;
                }

                j--;


            }

            i += std::max(delta1[text[i]], delta2[j]);
        }
        return false;
    }
};