#pragma once

#include <cmath>
#include "core_types.h"


uint32 modularExponentiation(uint32 base, uint32 e, uint32 mod) {
    if (mod == 1) return 0;

    uint32 i = 0;
    uint32 c = 1;

    while (i < e) {
        c = (c * base) % mod;
        i++;
    }
    return c;
}

/**
 * Fermat primality test
 */
uint32 isPrime(uint32 x, uint32 k = 3) {
    if (x <= 1) return false;
    if (x == 2 || x == 3) return true;

    uint32 a = 2 + rand() % (x - 2);

    for (uint32 i = 0; i < k; i++) {
        if ((static_cast<uint32>(std::pow(a, x - 1)) % x) != 1) {
            return false;
        }
//        if (modularExponentiation(a, x - 1, x) != 1) {
//            return false;
//        }
    }
    return true;
}