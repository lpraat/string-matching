#include "core_types.h"
#include "test_utils.h"
#include "boyer_moore.h"
#include "rabin_karp_3.h"
#include "rabin_karp_1.h"
#include "galil_seiferas.h"
#include "naive.h"
#include "rabin_karp_2.h"
#include <vector>
#include <string>
#include <chrono>
#include <iostream>


template <typename T>
void benchStringMatcher(const std::string& fileName, uint32 numSamples = 30) {
    std::vector<uint32> textLenghts {100000};
    std::vector<uint32> patLengths {25, 50, 100, 300, 500};


    for (uint32 i = 0; i < textLenghts.size(); i++) {
        std::string fName = "/Users/lpraat/develop/aapp/plot/data/tpt/";
        fName += std::to_string(textLenghts[i]);
        fName += fileName;

        FILE * f = fopen(fName.c_str(), "w");

        if (f == nullptr) {
            std::cout << "Error in creating the file";
        }

        uint32 offset;

        std::string text = generateTestStringAscii(textLenghts[i]);


        for (uint32 j = 0; j < patLengths.size(); j++) {

            std::string pattern = generatePatternAscii(patLengths[j]);
            std::string thisText = text + pattern;

            float32 total = 0;
            uint32 toAverage = 0;

            for (uint32 _ = 0; _ < numSamples; _++) {

                auto begin = std::chrono::high_resolution_clock::now();
                T stringMatcher(pattern);
                stringMatcher.searchIn(thisText, &offset);
                auto end = std::chrono::high_resolution_clock::now();

                if (offset == text.length()) {
                    auto took = std::chrono::duration_cast<std::chrono::duration<float>>(end - begin);
                    total += took.count();
                    toAverage += 1;
                }

                offset = 0;
            }

            if (toAverage > 0) {
                total /= toAverage;
                total *= 1e3;
                fprintf(f, "%d,%f\n", patLengths[j], total);
            }

        }

        std::cout << "Writing " << fName << std::endl;
        fclose(f);
    }

}

int main() {
    benchStringMatcher<RabinKarp1>("rabin_karp1.txt");
    benchStringMatcher<RabinKarp2>("rabin_karp2.txt");
    benchStringMatcher<RabinKarp3>("rabin_karp3.txt");
    return 0;
}