#include "test_utils.h"
#include "boyer_moore.h"
#include "rabin_karp_3.h"
#include "galil_seiferas.h"
#include "rabin_karp_2.h"
#include "rabin_karp_1.h"
#include "boyer_moore_simple.h"
#include "naive.h"
#include <iostream>


template <typename T>
void test() {
    // Test match
    for (uint32 i = 5; i < 1000; i++) {

        std::string pattern = generatePatternAscii(i+1);
        std::string text = generateTestStringAscii((i+1)*10);

        text += pattern;

        T stringMatcher(pattern);

        uint32 realOffset = (i+1)*10;
        uint32 offset;


        if (!stringMatcher.searchIn(text, &offset)) {
            std::cout << "Failed at " << std::endl;
            std::cout << "Text is " << text << std::endl;
            std::cout << "Pattern is " << pattern << std::endl;
            throw std::runtime_error("error");
        } else {
            if (offset != realOffset) {
                std::cout << "Failed at " << std::endl;
                std::cout << "Text is " << text << std::endl;
                std::cout << "Pattern is " << pattern << std::endl;
                throw std::runtime_error("error");
            }
        }
    }

    // Test no match
    for (uint32 i = 5; i < 1000; i++) {

        std::string p = "there will never be a pat like this";

        std::string text = generateTestStringAscii((i+1)*10);

        T stringMatcher(p);

        uint32 offset;
        if (stringMatcher.searchIn(text, &offset)) {
            std::cout << "Failed at " << std::endl;
            std::cout << "Text is " << text << std::endl;
            throw std::runtime_error("error");
        }
    }
}

void testRabinKarp1() {
    // Test match
    for (uint32 i = 5; i < 1000; i++) {

        std::string pattern = generatePatternAscii(i+1);
        std::string text = generateTestStringAscii((i+1)*10);

        text += pattern;

        RabinKarp1 rk1(pattern);

        uint32 realOffset = (i+1)*10;
        uint32 offset;

        if (!rk1.searchIn(text, &offset)) {
            std::cout << "Failed at " << std::endl;
            std::cout << "Text is " << text << std::endl;
            std::cout << "Pattern is " << pattern << std::endl;
            throw std::runtime_error("error");
        } else {
            if (offset != realOffset) {
                // Failing here is fine, false positive
            }
        }
    }
}

int main() {
    test<Naive>();
    test<BoyerMoore>();
    test<BoyerMooreSimple>();
    test<GalilSeiferas>();
    test<RabinKarp2>();
    test<RabinKarp3>();
    testRabinKarp1();
    return 0;
}


