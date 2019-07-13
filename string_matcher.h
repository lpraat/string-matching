#pragma once

#include <string>
#include "core_types.h"

class StringMatcher {
protected:
    std::string pat;
    uint32 patLength;

    explicit StringMatcher(const std::string& pat) : pat(pat) {
        patLength = pat.length();
    }

    /**
     * Assumes text.length() >= patLength
     */
    virtual bool searchIn(const std::string &text, uint32 *offset) = 0;
};