#pragma once

#include <stdint.h>

class TRndGen {
public:
    TRndGen(uint32_t seed)
        : Seed(seed)
        , Multiplier(1103515245)
        , Increment(12345)
    {
    }
    void Reset(uint32_t seed) {
        Seed = seed;
    }
    uint32_t Next() {
        uint32_t res = Extract(Seed);
        Seed = Seed * Multiplier;
        Seed += Increment;
        return res;
    }
private:
    uint32_t Extract(uint32_t x) {
        x <<= 1;
        x >>= 17;
        return x;
    }
private:
    uint32_t Seed;
    uint32_t Multiplier;
    uint32_t Increment;
};
