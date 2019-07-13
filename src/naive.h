#pragma once

#include "core_types.h"
#include "string_matcher.h"
#include <vector>
#include <string>


class Naive : StringMatcher {
private:

public:

    explicit Naive(const std::string& pat) : StringMatcher(pat) {
    }

    bool searchIn(const std::string &text, uint32 *offset) override {

        for (uint32 i = 0; i < text.length() - patLength + 1; i++) {
            uint32 j = 0;
            uint32 k = i;

            while (j < patLength && pat[j] == text[k]) {
                j++;
                k++;
            }

            if (j == patLength) {
                *offset = i;
                return true;
            }
        }

        return false;
    }

};

