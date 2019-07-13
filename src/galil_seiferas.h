#pragma once

#include "core_types.h"
#include <string>
#include <cmath>

class GalilSeiferas {

private:
    uint32 p, q, s, p1, q1, p2, q2;
    std::string pat;
    uint32 patLength;

    uint32 k = 4;
    uint32 offset;

    bool found = false;

public:

    explicit GalilSeiferas(const std::string &pat) : pat(pat), p{0}, q{0}, s{0}, p1{1}, q1{0}, p2{0}, q2{0} {
        patLength = pat.length();
    }

    void newp1(const std::string &text) {
        while (pat[s + q1] == pat[s + p1 + q1]) {
            q1++;
        }
        if (p1 + q1 >= k * p1) {
            p2 = q1;
            q2 = 0;
            newp2(text);
        } else {
            if (s + p1 + q1 == patLength) {
                search(text);
            } else {
                p1 += std::max(1u, 1 + q / k);
                q1 = 0;
                newp1(text);
            }
        }
    }

    void newp2(const std::string &text) {
        while (pat[s + p2 + q2] == pat[s + q2] && p2 + q2 < k * p2) {
            q2++;
        }
        if (p2 + q2 == k * p2) {
            parse(text);
        } else if (s + p2 + q2 == patLength) {
            search(text);
        } else {
            if (q2 == p1 + q1) {
                p2 = p2 + p1;
                q2 = q2 - p1;
            } else {
                p2 += std::max(1u, 1 + q / k);
                q2 = 0;
            }
            newp2(text);
        }
    }

    void parse(const std::string &text) {
        while (true) {
            while (pat[s + q1] == pat[s + p1 + q1]) {
                q1++;
            }
            while (p1 + q1 >= k*p1) {
                s += p1;
                q1 -= p1;
            }
            p1 += std::max(1u, 1 + q / k);
            q1 = 0;
            if (p1 >= p2)
                break;
        }
        newp1(text);
    }

    bool searchIn(const std::string &text, uint32 *offset) {
        found = false;
        newp1(text);

        *offset = this->offset;
        return found;
    }

    void search(const std::string &text) {
        uint32 textLength = text.length();
        while (p <= textLength - patLength) {

            while (p + s + q < textLength && pat[s + q] == text[p + s + q]) {
                q++;
            }

            if (q == patLength - s) {
                bool match = true;
                for (uint32 i = 0; i <= s; i++) {
                    if (pat[i] != text[p+i]) {
                        match = false;
                    }
                }

                if (match) {
                    found = true;
                    offset = p;
                    return;
                }
            }

            if (q == p1 + q1) {
                p += p1;
                q -= p1;
            } else {
                p += std::max(1u, 1 + q / k);
                q = 0;
            }
        }
    }


};

