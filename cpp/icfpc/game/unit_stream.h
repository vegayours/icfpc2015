#pragma once

#include "common/unit.h"
#include "common/rnd_gen.h"

#include <folly/FBVector.h>

#include <stdint.h>

class TUnitStream {
public:
    TUnitStream(uint32_t seed, uint32_t limit, folly::fbvector<TUnit> units);
    ~TUnitStream();
    bool Next(TUnit& unit);
    void Reset(uint32_t seed, uint32_t limit);
private:
    TRndGen Rnd;
    uint32_t Available;
    folly::fbvector<TUnit> Units;
};
