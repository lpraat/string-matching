#include "core_types.h"
#include "test_utils.h"
#include "boyer_moore.h"
#include <vector>
#include <string>
#include <chrono>
#include <iostream>


template <typename T>
void benchStringMatcher(const std::string& fileName, uint32 numSamples = 30) {
    uint32 textLength = 10000000;

    std::vector<uint32> alphabetLengths {2, 4, 8, 16, 32, 64};
    std::vector<uint32> patLengths {5, 10, 25, 50, 100, 300, 500, 750, 1000, 2500, 5000, 10000, 15000, 20000, 50000};


    for (uint32 i = 0; i < alphabetLengths.size(); i++) {
        std::string fName = "/Users/lpraat/develop/aapp/plot/data/alpha/";
        fName += std::to_string(alphabetLengths[i]);
        fName += fileName;

        FILE * f = fopen(fName.c_str(), "w");

        if (f == nullptr) {
            std::cout << "Error in creating the file";
        }

        uint32 offset;

        std::string text = generateTestStringAscii(textLength, alphabetLengths[i]);

        for (uint32 j = 0; j < patLengths.size(); j++) {

            std::string pattern = generatePatternAscii(patLengths[j], alphabetLengths[i]);
            std::string thisText = text + pattern;

            float32 total = 0;

            for (uint32 _ = 0; _ < numSamples; _++) {

                auto begin = std::chrono::high_resolution_clock::now();
                T stringMatcher(pattern);
                stringMatcher.searchIn(thisText, &offset);
                auto end = std::chrono::high_resolution_clock::now();

                auto took = std::chrono::duration_cast<std::chrono::duration<float>>(end - begin);
                total += took.count();

                offset = 0;
            }

            total /= numSamples;
            total *= 1e6;
            fprintf(f, "%d,%f\n", patLengths[j], total);

        }

        std::cout << "Writing " << fName << std::endl;
        fclose(f);
    }

}

int main() {
    for (uint8 i = 0; i < 4; i++) {
        std::cout << "Remember to remove return when offset is found" << std::endl;
    }
    benchStringMatcher<BoyerMoore>("boyer_moore.txt");
    return 0;
}