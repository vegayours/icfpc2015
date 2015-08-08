#include "unit_stream.h"

TUnitStream::TUnitStream(uint32_t seed, uint32_t limit, folly::fbvector<TUnit> units)
    : Rnd(seed)
    , Available(limit)
    , Units(std::move(units))
{
}

TUnitStream::~TUnitStream()
{
}

bool TUnitStream::Next(TUnit& unit) {
    if (Available > 0) {
        size_t next = Rnd.Next() % Units.size();
        unit = Units[next];
        Available--;
        return true;
    }
    return false;
}
void TUnitStream::Reset(uint32_t seed, uint32_t limit) {
    Available = limit;
    Rnd.Reset(seed);
}
